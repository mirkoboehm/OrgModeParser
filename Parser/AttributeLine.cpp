#include "AttributeLine.h"

namespace OrgMode {

class AttributeLine::Private {
public:
public:
    QString key_;
    QString value_;
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

void AttributeLine::setProperty(const QString &key, const QString &value)
{
    d->key_ = key;
    d->value_ = value;
}

QString AttributeLine::key() const
{
    return d->key_;
}

QString AttributeLine::value() const
{
    return d->value_;
}

bool AttributeLine::isElementValid() const
{
    return !d->key_.isEmpty();
}

QString AttributeLine::description() const
{
    return tr("%1: %2").arg(d->key_).arg(d->value_);
}


}

