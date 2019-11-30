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
#ifndef INCOMPLETECLOCKLINE_H
#define INCOMPLETECLOCKLINE_H

#include <memory>

#include <QCoreApplication>
#include <QDateTime>
#include <OrgElement.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT ClockLine : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(ClockLine)
public:
    typedef QSharedPointer<ClockLine> Pointer;

    explicit ClockLine(const QString& line, OrgElement* parent = nullptr);
    explicit ClockLine(OrgElement* parent = nullptr);
    ClockLine(ClockLine&&);
    ClockLine& operator=(ClockLine&&);
    ~ClockLine() override;


    void setStartTime(const QDateTime& start);
    QDateTime startTime() const;

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    struct Private;
    std::unique_ptr<Private> d;
};

}

#endif // INCOMPLETECLOCKLINE_H
