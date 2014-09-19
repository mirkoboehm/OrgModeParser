#include <QIODevice>
#include <QTextStream>
#include <QRegularExpression>
#include <QtDebug>


#include "Parser.h"
#include "OrgElement.h"
#include "OrgLine.h"
#include "OrgFile.h"
#include "Headline.h"
#include "Exception.h"
#include "OrgFileContent.h"

namespace OrgMode {

class Parser::Private {
public:
    Private(Parser* parser)
        : parser_(parser)
    {}

    /** @brief Parse a sequence of top level elements, considering it as one file unit. */
    OrgFile::Pointer parseOrgFile(OrgFileContent* content, const QString& filename) const;

    OrgElement::Pointer parseOrgElement(OrgElement::Pointer parent, OrgFileContent* content) const;
    OrgElement::Pointer parseHeadline(OrgElement::Pointer parent, OrgFileContent* content) const;
    OrgElement::Pointer parseOrgLine(OrgElement::Pointer parent, OrgFileContent* content) const;

private:
    Parser* parser_;
};

OrgFile::Pointer Parser::Private::parseOrgFile(OrgFileContent *content, const QString &filename) const
{
    auto file = OrgFile::Pointer(new OrgFile);
    file->setFileName(filename);
    while(!content->atEnd()) {
        file->addChild(parseOrgElement(file, content));
    }
    return file;
}

OrgElement::Pointer Parser::Private::parseOrgElement(OrgElement::Pointer parent, OrgFileContent *content) const
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
            auto self = Headline::Pointer(new Headline(parent.data()));
            auto const description = match.captured(2);
            self->setCaption(description);
            while(OrgElement::Pointer child = parseOrgElement(self, content)) {
                self->addChild(child);
            }
            return self;
        }
    } else {
        //Not a headline, parse it as a non-recursive element.
        content->ungetLine(line);
        //(For now, only lines are parsed):
        return parseOrgLine(parent, content);
    }
}

OrgElement::Pointer Parser::Private::parseOrgLine(OrgElement::Pointer parent, OrgFileContent *content) const
{
    Q_UNUSED(parent);
    if (content->atEnd()) {
        return OrgElement::Pointer();
    }
    const QString text = content->getLine();
    const auto element = OrgElement::Pointer(new OrgLine(text, parent.data()));
    return element;
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

OrgElement::Pointer Parser::parse(QTextStream *data, const QString fileName) const
{
    Q_ASSERT(data);
    OrgFileContent content(data);
    return d->parseOrgFile(&content, fileName);
}

}
