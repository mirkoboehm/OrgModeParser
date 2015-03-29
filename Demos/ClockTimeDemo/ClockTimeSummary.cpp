#include <numeric>
#include <iostream>

#include <QTextStream>
#include <QFile>
#include <QtDebug>
#include <QDateTime>

#include <OrgFile.h>
#include <OrgElement.h>
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
    auto const isToday = [today](const CompletedClockLine::Pointer& line) {
        if (line->startTime().date() == today || line->endTime().date() == today) {
            return true;
        } else {
            return false;
        }
    };
    auto const todaysClockLines = findElements<CompletedClockLine>(toplevel_, -1, isToday);
    return accumulate(begin(todaysClockLines), end(todaysClockLines), 0,
                           [](int i, const CompletedClockLine::Pointer& clock) { return i + clock->duration(); } );
}

int ClockTimeSummary::secondsClockedThisWeek() const
{
    auto const today = QDate::currentDate();
    auto const monday = today.addDays(1-today.dayOfWeek());
    auto const sunday = monday.addDays(7);
    auto const isThisWeek = [monday, sunday](const CompletedClockLine::Pointer& line) {
        if ((line->startTime().date() >= monday && line->startTime().date() <= sunday)
                || (line->endTime().date() >=monday && line->startTime().date() <= sunday)) {
            return true;
        } else {
            return false;
        }
    };
    auto const clocklines = findElements<CompletedClockLine>(toplevel_, -1, isThisWeek);
    return accumulate(begin(clocklines), end(clocklines), 0,
                      [](int i, const CompletedClockLine::Pointer& clock) { return i + clock->duration(); } );
}

template <typename T>
T* findParent(OrgElement* element)
{
    if (!element) return 0;
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
        return element.dynamicCast<CompletedClockLine>() == 0;
    };
    auto clocklines = findElements<ClockLine>(toplevel_, -1, notCompleted);
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
            const int secondsToNow = lastInitiatedClockline->startTime().secsTo(QDateTime::currentDateTime());
            currentlyClockedTime = hoursAndMinutes(secondsToNow);
            currentTask = headline->caption();
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

QString ClockTimeSummary::hoursAndMinutes(int seconds)
{
    const QChar fillChar(QChar::fromLatin1('0'));
    const int hours = seconds / 3600;
    const int minutes = (seconds - hours*3600) / 60;
    const QString time(tr("%1:%2")
                       .arg(hours, 2, 10, fillChar)
                       .arg(minutes, 2, 10, fillChar));
    return time;
}
