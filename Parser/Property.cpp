#include "Property.h"

namespace OrgMode {

class Property::Private {
public:
    Private(QString key_, QString value_, Property::Operation operation_)
        : key(key_)
        , value(value_)
        , operation(operation_)
    {}

    bool operator==(const Private& other) const {
        return key == other.key
                && value == other.value
                && operation == other.operation;
    }

    QString key;
    QString value;
    Property::Operation operation;
};

Property::Property()
    : Property(QString(), QString())
{
}

Property::Property(const QString &key, const QString &value, Operation op)
    : d(new Private(key, value, op))
{
}

Property::Property(const Property& other)
    : Property(other.key(), other.value())
{
}

Property::~Property()
{
    delete d; d = 0;
}

bool Property::operator==(const Property& other) const
{
    return *d == *other.d;
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
