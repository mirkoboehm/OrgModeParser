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
#include "OrgLine.h"

namespace OrgMode {

OrgLine::OrgLine(OrgElement *parent)
    : OrgLine(QString(), parent)
{
}

OrgLine::OrgLine(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(0)
{
}

OrgLine::~OrgLine()
{
}

bool OrgLine::isElementValid() const
{
    return !line().isNull(); // an empty string is not null
}

QString OrgLine::mnemonic() const
{
    return QLatin1String("OrgLine");
}

QString OrgLine::description() const
{
    return tr("%1").arg(line());
}

}
