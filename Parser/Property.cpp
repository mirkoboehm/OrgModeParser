#include "Property.h"

namespace OrgMode {

class Property::Private {
public:
    Property::Operation operation = Property::Property_Define;
    QString key;
    QString value;
};

Property::Property()
    : Property(QString(), QString())
{
}

Property::Property(const QString &key, const QString &value)
    : d(new Private)
{
    d->key = key;
    d->value = value;
}

Property::Property(const Property& other)
    : Property(other.key(), other.value())
{
}

Property::~Property()
{
    delete d; d = 0;
}

QString Property::key() const
{
    return d->key;
}

void Property::setKey(const QString &key)
{
    d->key = key;
}

QString Property::value() const
{
    return d->value;
}

void Property::setValue(const QString &value) const
{
    d->value = value;
}

Property::Operation Property::operation() const
{
    return d->operation;
}

void Property::setOperation(Property::Operation op)
{
    d->operation = op;
}

}
