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
#ifndef CLOCKTIMESUMMARY_H
#define CLOCKTIMESUMMARY_H

#include <QObject>
#include <OrgElement.h>

class ClockTimeSummary : public QObject
{
    Q_OBJECT
public:
    explicit ClockTimeSummary(const QStringList& orgfiles, QObject *parent = nullptr);
    int secondsClockedToday() const;
    int secondsClockedThisWeek() const;

    void report(bool promptMode, int columns);

private:
    QString hoursAndMinutes(long seconds);

    OrgMode::OrgElement::Pointer toplevel_;

};

#endif // CLOCKTIMESUMMARY_H
