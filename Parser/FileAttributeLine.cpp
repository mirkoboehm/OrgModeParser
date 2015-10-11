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
#include "FileAttributeLine.h"

namespace OrgMode {

class FileAttributeLine::Private {
public:
};

FileAttributeLine::FileAttributeLine(OrgMode::OrgElement *parent)
    : FileAttributeLine(QString(), parent)
{
}

FileAttributeLine::FileAttributeLine(const QString &line, OrgElement *parent)
    : AttributeLine(line, parent)
    , d(new Private)
{
}

FileAttributeLine::~FileAttributeLine()
{
    delete d; d = 0;
}

QString FileAttributeLine::mnemonic() const
{
    return tr("FileAttr");
}

}
