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

AttributeLine::AttributeLine(AttributeLine && other) = default;
AttributeLine& AttributeLine::operator=(AttributeLine &&other) = default;
AttributeLine::~AttributeLine() = default;

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

