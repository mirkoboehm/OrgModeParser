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
#ifndef ORGMODE_PARSER_EXCEPTION_H
#define ORGMODE_PARSER_EXCEPTION_H

#include <QCoreApplication>

#include <stdexcept>

#include <QString>

#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT Exception : public std::runtime_error
{
public:
    explicit Exception(const QString& message);
    ~Exception() throw();
    QString message() const;

private:
    QString m_message;
};

class ORGMODEPARSER_EXPORT NotImplementedException : public Exception
{
    Q_DECLARE_TR_FUNCTIONS(NotImplementedException)
public:
    explicit NotImplementedException(const QString& message = tr("Not implemented!"));
};

class ORGMODEPARSER_EXPORT RuntimeException : public Exception
{
public :
    explicit RuntimeException(const QString& message);
};

}

#endif // ORGMODE_PARSER_EXCEPTION_H
