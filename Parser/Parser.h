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
#ifndef PARSER_H
#define PARSER_H

#include <memory>

#include <QObject>

#include "orgmodeparser_export.h"
#include <OrgElement.h>

class QTextStream;

namespace OrgMode {

class ORGMODEPARSER_EXPORT Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);
    ~Parser() override;

    OrgElement::Pointer parse(QTextStream* data, const QString& fileName = QString()) const;
private:
    struct Private;
    std::unique_ptr<Private> d;
};

QString ORGMODEPARSER_EXPORT version();
}

#endif // PARSER_H
