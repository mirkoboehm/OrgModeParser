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
#include "OrgFile.h"

namespace OrgMode {

class OrgFile::Private {
public:
    QString fileName_;
};

OrgFile::OrgFile(OrgElement *parent)
    : OrgElement(parent)
    , d(new Private)
{
}

OrgFile& OrgFile::operator=(const OrgFile& other)
{
    *d = *other.d;
    return *this;
}

OrgFile::OrgFile(OrgFile && other) = default;
OrgFile& OrgFile::operator=(OrgFile &&other) = default;
OrgFile::~OrgFile() = default;

void OrgFile::setFileName(const QString &fileName)
{
    d->fileName_ = fileName;
}

QString OrgFile::fileName() const
{
    return d->fileName_;
}

bool OrgFile::isElementValid() const
{
    return true;
}

QString OrgFile::mnemonic() const
{
    return QLatin1String("OrgFile");
}

QString OrgFile::description() const
{
    return tr("%1 (%2 elements)")
            .arg(fileName().isEmpty() ? tr("<unnamed>") : fileName())
            .arg(children().count());
}

}
