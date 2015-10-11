/** OrgModeParser - a parser for Emacs Org Mode files, written in C++.
    Copyright (C) 2015 Mirko Boehm

    This file is part of OrgModeParser.
    OrgModeParser is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, version 3 of the
    License.

    OrgModeParser is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the GNU General Public License for more details. You should
    have received a copy of the GNU General Public License along with
    OrgModeParser. If not, see <http://www.gnu.org/licenses/>.
*/
#include "Exception.h"
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

Property::Property(const QString &key, const QString &value, Operation op)
    : d(new Private(key, value, op))
{
}

Property::Property()
    : Property(QString(), QString())
{
}

Property::Property(const Property& other)
    : Property(other.key(), other.value(), other.operation())
{
}

Property::~Property()
{
}

Property& Property::operator=(const Property &other)
{
    if (this != &other) {
        *d = *(other.d);
    }
    return *this;
}

bool Property::operator==(const Property& other) const
{
  return *d == *other.d;
}

bool Property::isValid() const
{
    return !key().isEmpty();
}

void Property::apply(const Property &token)
{
    if (token.operation() == Property::Property_Define) {
        d->key = token.key();
        d->value = token.value();
    } else if (token.operation() == Property::Property_Add) {
        d->key = token.key();
        d->value = QString::fromLatin1("%1 %2").arg(d->value).arg(token.value());
    } else {
        Q_ASSERT_X(false, Q_FUNC_INFO, "Unsupported operation!");
    }
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
