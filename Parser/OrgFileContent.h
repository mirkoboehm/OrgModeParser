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
#ifndef ORGFILECONTENT_H
#define ORGFILECONTENT_H

#include <QStringList>
#include <QSharedPointer>

#include "orgmodeparser_export.h"

class QTextStream;

namespace OrgMode {

/** @brief OrgFileContent represents a data file and adds unget functionality for lines.
 *  It is not exported.
 */
class ORGMODEPARSER_EXPORT OrgFileContent
{
public:
    typedef QSharedPointer<OrgFileContent> Pointer;

    explicit OrgFileContent(QTextStream* data = nullptr);

    QString getLine();
    void ungetLine(const QString& line);
    void ungetLines(const QStringList& lines);
    bool atEnd() const;

private:
    QTextStream* data_;
    QStringList lines_;
};

}

#endif // ORGFILECONTENT_H
