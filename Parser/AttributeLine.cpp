#include "AttributeLine.h"

namespace OrgMode {

class AttributeLine::Private {
public:
    Property property_;
};

AttributeLine::AttributeLine(OrgElement *parent)
    : AttributeLine(QString(), parent)
{

}

AttributeLine::AttributeLine(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(new Private)
{
}

AttributeLine::~AttributeLine()
{
    delete d; d = 0;
}

void AttributeLine::setProperty(const Property &property)
{
    d->property_ = property;
}

Property AttributeLine::property() const
{
    return d->property_;
}

QString AttributeLine::key() const
{
    return d->property_.key();
}

QString AttributeLine::value() const
{
    return d->property_.value();
}

bool AttributeLine::isElementValid() const
{
    return !d->property_.isValid();
}

QString AttributeLine::description() const
{
    return tr("%1: %2").arg(d->property_.key()).arg(d->property_.value());
}

}

