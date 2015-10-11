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
#include <QTextStream>

#include "OrgFileContent.h"

namespace OrgMode {

OrgFileContent::OrgFileContent(QTextStream *data)
    : data_(data)
{
}

QString OrgFileContent::getLine()
{
    if (!lines_.isEmpty()) {
        return lines_.takeFirst();
    } else if (data_) {
        return data_->readLine();
    } else {
        return QString();
    }
}

void OrgFileContent::ungetLine(const QString &line)
{
    if (!line.isNull()) {
        lines_.prepend(line);
    }
}

void OrgFileContent::ungetLines(const QStringList &lines)
{
    if (!lines.isEmpty()) {
        lines_ = lines + lines_;
    }
}

bool OrgFileContent::atEnd() const
{
    return lines_.isEmpty() && (data_ == 0 || data_->atEnd());
}

}
