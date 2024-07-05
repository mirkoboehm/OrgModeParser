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
#include <iostream>

#include <QTextStream>
#include <QFile>
#include <QtDebug>
#include <QDateTime>

#include <OrgFile.h>
#include <OrgElement.h>
#include <TimeInterval.h>
#include <Clock.h>
#include <Parser.h>
#include <Exception.h>
#include <ClockLine.h>
#include <CompletedClockLine.h>
#include <Headline.h>
#include <FindElements.h>

#include "ClockTimeSummary.h"

using namespace std;
using namespace OrgMode;

ClockTimeSummary::ClockTimeSummary(const QStringList &orgfiles, QObject *parent)
    : QObject(parent)
    , toplevel_(new OrgFile)
{
    for(const QString& filename : orgfiles) {
        Parser parser;
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            throw RuntimeException(tr("Unable to open file %1!").arg(filename));
        }
        QTextStream stream(&file);
        OrgElement::Pointer orgfile = parser.parse(&stream, filename);
        toplevel_->addChild(orgfile);
    }
}

int ClockTimeSummary::secondsClockedToday() const
{
    auto const today = QDate::currentDate();
    const TimeInterval day(today, today.addDays(1));
    const Clock clock(toplevel_);
    return clock.duration(day);
}

int ClockTimeSummary::secondsClockedThisWeek() const
{
    auto const today = QDate::currentDate();
    auto const monday = today.addDays(1-today.dayOfWeek());
    const TimeInterval week(monday, monday.addDays(7));
    const Clock clock(toplevel_);
    return clock.duration(week);
}

template <typename T>
T* findParent(OrgElement* element)
{
    if (!element) return nullptr;
    auto castedElement = dynamic_cast<T*>(element);
    if (castedElement) {
        return castedElement;
    } else {
        return findParent<T>(element->parent());
    }
}

void ClockTimeSummary::report(bool promptMode, int columns)
{
    //The data to report:
    QString currentlyClockedTime = tr("--:--");
    QString currentTask = tr("...");
    QString clockedTime;
    //Find all clocklines that are incomplete (not closed):
    auto const notCompleted = [](const ClockLine::Pointer& element) {
        return element.dynamicCast<CompletedClockLine>() == nullptr;
    };
    auto clocklines = findElements<ClockLine>(toplevel_, notCompleted);
    //Sort by start time, to determine the latest task that was started:
    auto const startedLater = [](const ClockLine::Pointer& left, const ClockLine::Pointer& right) {
        return left->startTime() > right->startTime();
    };
    sort(clocklines.begin(), clocklines.end(), startedLater);
    //Find the headline associated with the youngest unclosed clock line:
    if (!clocklines.isEmpty()) {
        auto const lastInitiatedClockline = clocklines.at(0);
        Headline* headline = findParent<Headline>(lastInitiatedClockline->parent());
        //Prepare the bits of the report that deal with the current task:
        if (headline) {
            const long secondsToNow = lastInitiatedClockline->startTime().secsTo(QDateTime::currentDateTime());
            currentlyClockedTime = hoursAndMinutes(secondsToNow);
            currentTask = headline->caption().simplified();
        }
    }
    //Prepare the display of the running time today and this week:
    clockedTime=tr("%1/%2").arg(hoursAndMinutes(secondsClockedToday())).arg(hoursAndMinutes(secondsClockedThisWeek()));
    const QString line = tr("%1: %3 %2").arg(currentlyClockedTime).arg(clockedTime);
    const int remainingChars = columns - line.length() + 2; //add space for the %3 placeholder
    if (currentTask.length() > remainingChars) {
        currentTask = tr("%1...").arg(currentTask.mid(0, remainingChars-3));
    }
    const QString output = line.arg(currentTask, -remainingChars, QChar::fromLatin1(' '));
    wcout << output.toStdWString();
    if (!promptMode) {
        wcout << endl;
    }
}

QString ClockTimeSummary::hoursAndMinutes(long seconds)
{
    const QChar fillChar(QChar::fromLatin1('0'));
    const long hours = seconds / 3600;
    const long minutes = (seconds - hours*3600) / 60;
    const QString time(tr("%1:%2")
                       .arg(hours, 2, 10, fillChar)
                       .arg(minutes, 2, 10, fillChar));
    return time;
}
