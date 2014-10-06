#include <QIODevice>
#include <QTextStream>
#include <QRegularExpression>
#include <QtDebug>


#include "Parser.h"
#include "OrgElement.h"
#include "OrgLine.h"
#include "FileAttributeLine.h"
#include "OrgFile.h"
#include "Headline.h"
#include "Properties.h"
#include "ClockLine.h"
#include "Exception.h"
#include "OrgFileContent.h"
#include "Drawer.h"
#include "DrawerEntry.h"
#include "DrawerClosingEntry.h"

namespace OrgMode {

class Parser::Private {
public:
    typedef std::pair<OrgFile::Pointer, QSharedPointer<OrgFileContent>> ParseRunOutput;

    Private(Parser* parser)
        : parser_(parser)
    {}

    /** @brief First parse pass that provide the file-level attributes.
     * @return The parse results and the content for the second pass in a std::pair.
     */
    ParseRunOutput parseOrgFileFirstPass(const OrgFileContent::Pointer& content, const QString& filename) const;
    /** @brief Parse a sequence of top level elements, considering it as one file unit. */
    OrgFile::Pointer parseOrgFile(OrgFileContent::Pointer content, const QString& filename) const;

    OrgElement::Pointer parseOrgElement(const OrgElement::Pointer& parent, const OrgFileContent::Pointer& content) const;
    OrgElement::Pointer parseOrgLine(const OrgElement::Pointer& parent, const OrgFileContent::Pointer& content) const;
    OrgElement::Pointer parseClockLine(const OrgElement::Pointer& parent, const OrgFileContent::Pointer& content) const;
    OrgElement::Pointer parseFileAttributeLine(const OrgElement::Pointer& parent, const OrgFileContent::Pointer& content) const;
    OrgElement::Pointer parseDrawerLine(const OrgElement::Pointer& parent, const OrgFileContent::Pointer& content) const;

    Parser* parser_;
    Properties::PropertiesMap filePropertiesAfterFirstPass_;
};

Parser::Private::ParseRunOutput Parser::Private::parseOrgFileFirstPass(const OrgFileContent::Pointer &content, const QString &filename) const
{
    QSharedPointer<OrgFileContent> output(new OrgFileContent);
    OrgFile::Pointer file(new OrgFile);
    file->setFileName(filename);
    QStringList lines;
    while(!content->atEnd()) {
        if (OrgElement::Pointer element = parseFileAttributeLine(file, content)) {
            file->addChild(element);
            lines.append(element->line());
        } else {
            lines.append(content->getLine());
        }
    }
    output->ungetLines(lines);
    return std::make_pair(file, output);
}

OrgFile::Pointer Parser::Private::parseOrgFile(OrgFileContent::Pointer content, const QString &filename) const
{
    auto file = OrgFile::Pointer(new OrgFile);
    file->setFileName(filename);
    while(!content->atEnd()) {
        file->addChild(parseOrgElement(file, content));
    }
    return file;
}

OrgElement::Pointer Parser::Private::parseOrgElement(const OrgElement::Pointer &parent, const OrgFileContent::Pointer &content) const
{
    static QRegularExpression beginningOfHeadline(QStringLiteral("^([*]+)\\s+(.*)$"));
    //Let's see, is it a headline?
    const QString line = content->getLine();
    auto const match = beginningOfHeadline.match(line);
    if (match.hasMatch()) {
        //If so, is it at the same or a lower level than the current element?
        const QString structureMarker = match.captured(1);
        if (structureMarker.length() <= parent->level()) {
            //The matched element is at the same level as this element.
            //Stop and return, this element has been completely parsed:
            content->ungetLine(line);
            return OrgElement::Pointer(); // end recursing
        } else {
            //This is a new headline, parse it and it's children until another sibling or parent headline is discovered
            auto self = Headline::Pointer(new Headline(line, parent.data()));
            QString description = match.captured(2);
            static QRegularExpression tagsMatch(QStringLiteral("^(.+)(\\s+):(.+):\\s*$"));
            auto const match = tagsMatch.match(description);
            if (match.hasMatch()) {
                //We have tags:
                const QStringList tagsList = match.captured(3).split(QLatin1Char(':'));
                Headline::Tags tags;
                std::copy(tagsList.begin(), tagsList.end(), std::inserter(tags, tags.begin()));
                self->setTags(tags);
                //Set description to the remainder of the headline:
                description = match.captured(1).trimmed();
            }
            self->setCaption(description);
            while(OrgElement::Pointer child = parseOrgElement(self, content)) {
                self->addChild(child);
            }
            return self;
        }
    } else {
        //Not a headline, parse it as a non-recursive element.
        content->ungetLine(line);
        if (OrgElement::Pointer element = parseClockLine(parent, content)) {
            return element;
        } else if (OrgElement::Pointer element = parseFileAttributeLine(parent, content)) {
            return element;
        } else if (OrgElement::Pointer element = parseDrawerLine(parent, content)) {
            return element;
        } else {
            //Every line is an OrgLine, so this is the fallback:
            return parseOrgLine(parent, content);
        }
    }
}

OrgElement::Pointer Parser::Private::parseOrgLine(const OrgElement::Pointer &parent, const OrgFileContent::Pointer &content) const
{
    Q_UNUSED(parent);
    if (content->atEnd()) {
        return OrgElement::Pointer();
    }
    const QString text = content->getLine();
    const auto element = OrgElement::Pointer(new OrgLine(text, parent.data()));
    return element;
}

OrgElement::Pointer Parser::Private::parseClockLine(const OrgElement::Pointer& parent, const OrgFileContent::Pointer& content) const
{
    static QRegularExpression clockLineStructure(QStringLiteral("^(\\s*)CLOCK:\\s*\\[(.+)\\]--\\[(.+)\\]"));
    const QString line = content->getLine();
    auto const match = clockLineStructure.match(line);
    if (match.hasMatch()) {
        auto const format = QString::fromLatin1("yyyy-MM-dd ddd hh:mm");
        auto const startText = match.captured(2);
        const QDateTime start = QDateTime::fromString(startText, format);
        auto const endText = match.captured(3);
        const QDateTime end = QDateTime::fromString(endText, format);
        if (start.isValid() && end.isValid()) {
            auto self = ClockLine::Pointer(new ClockLine(line, parent.data()));
            self->setStartTime(start);
            self->setEndTime(end);
            return self;
        }
    }
    content->ungetLine(line);
    return OrgElement::Pointer();
}

OrgElement::Pointer Parser::Private::parseFileAttributeLine(const OrgElement::Pointer &parent, const OrgFileContent::Pointer &content) const
{
    static QRegularExpression fileAttributeStructure(QStringLiteral("\\#\\+(.+):\\s+(.*)$"));
    const QString line = content->getLine();
    auto const match = fileAttributeStructure.match(line);
    if (match.hasMatch()) {
        const QString key = match.captured(1);
        const QString value = match.captured(2);
        if (!key.isEmpty()) {
            auto self = new FileAttributeLine(line, parent.data());
            self->setProperty(key, value);
            return OrgElement::Pointer(self);
        }
    }
    content->ungetLine(line);
    return OrgElement::Pointer();
}

QStringList collectLines(const OrgElement::Pointer& element) {
    QStringList lines;
    lines << element->line();
    for(const OrgElement::Pointer child : element->children()) {
        lines << collectLines(child);
    }
    return lines;
}

OrgElement::Pointer Parser::Private::parseDrawerLine(const OrgElement::Pointer &parent, const OrgFileContent::Pointer &content) const
{
    static QRegularExpression drawerTitleStructure(QStringLiteral("^\\s+:(.+):\\s*(.*)$"));
    const QString line = content->getLine();
    auto const match = drawerTitleStructure.match(line);
    if (match.hasMatch()) {
        const QString name = match.captured(1);
        const QString value = match.captured(2);
        if (!value.isEmpty()) {
            content->ungetLine(line);
            return OrgElement::Pointer();
        }
        QStringList drawernames = filePropertiesAfterFirstPass_.value(QString::fromLatin1("DRAWERS"))
                .split(QRegExp(QLatin1String("\\s+")));
        if (drawernames.contains(name)) {
            //This is a drawer
            Drawer::Pointer self(new Drawer(line, parent.data()));
            self->setName(name);
            //Parse elements until :END: (complete) or headline (cancel)
            static QRegularExpression drawerEntryStructure(QStringLiteral("^\\s*:(.+):\\s*(.*)$"));
            while(!content->atEnd()) {
                const QString line = content->getLine();
                //FIXME TODO
                //Make "uncommittedElementLinesUngetter"
                //Refactor duplicated detection of headlines
                static QRegularExpression beginningOfHeadline(QStringLiteral("^([*]+)\\s+(.*)$"));
                auto const headlineMatch = beginningOfHeadline.match(line);
                if (headlineMatch.hasMatch()) {
                    const QStringList lines = QStringList() << collectLines(self) << line;
                    content->ungetLines(lines);
                    return OrgElement::Pointer();
                }
                auto const match = drawerEntryStructure.match(line);
                if (match.hasMatch()) {
                    const QString name = match.captured(1);
                    const QString value = match.captured(2).trimmed();
                    if (name == QStringLiteral("END")) {
                        //The end element, add it to the drawer, return
                        DrawerClosingEntry::Pointer child(new DrawerClosingEntry(line, self.data()));
                        child->setProperty(name, value);
                        self->addChild(child);
                        break;
                    } else {
                        //This is a drawer entry, specifying one key-value pair
                        DrawerEntry::Pointer child(new DrawerEntry(line, self.data()));
                        child->setProperty(name, value);
                        self->addChild(child);
                    }
                } else {
                    //The line is not a drawer entry, but located within a drawer.
                    //Consider it a regular OrgLine.
                    self->addChild(OrgLine::Pointer(new OrgLine(line, self.data())));
                }
            }
            return self;
        } else {
           //This is just a regular line that looks like a drawer, do nothing
        }
    }
    content->ungetLine(line);
    return OrgElement::Pointer();
}

Parser::Parser(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

Parser::~Parser()
{
    delete d; d = 0;
}

OrgElement::Pointer Parser::parse(QTextStream *data, const QString &fileName) const
{
    Q_ASSERT(data);
    OrgFileContent::Pointer content(new OrgFileContent(data));
    auto firstPassResults = d->parseOrgFileFirstPass(content, fileName);
    const Properties properties(firstPassResults.first);
    d->filePropertiesAfterFirstPass_ = properties.properties();
    return d->parseOrgFile(firstPassResults.second, fileName);
}

}
