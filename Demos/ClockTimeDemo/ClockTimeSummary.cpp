#include <numeric>

#include <QTextStream>
#include <QFile>
#include <QtDebug>

#include <OrgFile.h>
#include <OrgElement.h>
#include <Parser.h>
#include <Exception.h>
#include <ClockLine.h>
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
    auto const isToday = [this, today](const ClockLine::Pointer& line) {
        if (line->startTime().date() == today || line->endTime().date() == today) {
            return true;
        } else {
            return false;
        }
    };
    auto const todaysClockLines = findElements<ClockLine>(toplevel_, -1, isToday);
    return accumulate(begin(todaysClockLines), end(todaysClockLines), 0,
                           [](int i, const ClockLine::Pointer& clock) -> int { return i + clock->duration(); } );
}

int ClockTimeSummary::secondsClockedThisWeek() const
{
    return 0;
}
