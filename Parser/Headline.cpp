#include <QRegularExpression>
#include <QTextStream>
#include <QtDebug>

#include "Headline.h"
#include "Exception.h"
#include "OrgFileContent.h"

namespace OrgMode {

class Headline::Private {
public:
    QString caption_;
    QStringList lines_;
};

Headline::Headline()
    : d(new Private)
{
}

Headline::~Headline()
{
    delete d; d = 0;
}

QString Headline::caption() const
{
    return d->caption_;
}

void Headline::setCaption(const QString &caption)
{
    d->caption_ = caption;
}

void Headline::readFrom(OrgFileContent *content)
{
//    QRegularExpression re(QStringLiteral("^([*]+)\\s+(.*)$"));
//    d->lines_.clear();

//    while(!content->atEnd()) {
//        const QString line = content->getLine();
//        auto const match = re.match(line);
//        if (match.hasMatch()) {
//            const QString structureMarker = match.captured(1);
//            if (structureMarker.length() <= level()) {
//                // the matched element is at the same level as this element
//                // stop and return, this one is complete
//                content->ungetLine(line);
//                return;
//            }
//            const QString description = match.captured(2);
//            auto child = Pointer(new Headline);
//            child->setLevel(level()+1);
//            child->setCaption(description);
//            qDebug() << "Beginning of level" << child->level() << "headline found:" << line;
//            child->readFrom(content);
//            addChild(child);
//        } else {
//            d->lines_.append(line);
//        }
//    }
}

}
