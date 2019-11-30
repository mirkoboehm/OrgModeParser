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
#include "PropertyDrawer.h"

namespace OrgMode {

class PropertyDrawer::Private {
public:
};

PropertyDrawer::PropertyDrawer(OrgElement *parent)
    : PropertyDrawer(QString(), parent)
{
}

PropertyDrawer::PropertyDrawer(const QString &line, OrgElement *parent)
    : Drawer(line, parent)
    , d(new Private())
{
}

PropertyDrawer::PropertyDrawer(PropertyDrawer && other) = default;
PropertyDrawer& PropertyDrawer::operator=(PropertyDrawer &&other) = default;
PropertyDrawer::~PropertyDrawer() = default;

QString PropertyDrawer::mnemonic() const
{
    return tr("PropDrwr");
}

}
