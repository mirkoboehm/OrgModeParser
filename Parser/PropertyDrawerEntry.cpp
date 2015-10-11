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
#include "PropertyDrawerEntry.h"

namespace OrgMode {

class PropertyDrawerEntry::Private {
public:
};

PropertyDrawerEntry::PropertyDrawerEntry(OrgElement *parent)
    : PropertyDrawerEntry(QString(), parent)
{

}

PropertyDrawerEntry::PropertyDrawerEntry(const QString &line, OrgElement *parent)
    : DrawerEntry(line, parent)
    , d(new Private)
{
}

PropertyDrawerEntry::~PropertyDrawerEntry()
{
    delete d; d = 0;
}

QString PropertyDrawerEntry::mnemonic() const
{
    return tr("PrpDEntr");
}

QString PropertyDrawerEntry::description() const
{
    return tr("%1: %2 %3")
            .arg(property().key())
            .arg(property().operation() == Property::Property_Define ? tr("SET") : tr("ADD"))
            .arg(property().value());
}

}
