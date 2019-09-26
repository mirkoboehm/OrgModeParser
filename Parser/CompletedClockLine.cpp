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
#include "CompletedClockLine.h"
#include "TimeInterval.h"

namespace OrgMode {

class CompletedClockLine::Private {
public:
    QDateTime end_;
};

CompletedClockLine::CompletedClockLine(const QString &line, OrgElement *parent)
    : ClockLine(line, parent)
    , d(new Private)
{

}

CompletedClockLine::CompletedClockLine(OrgElement *parent)
    : CompletedClockLine(QString(), parent)
{
}

void CompletedClockLine::setEndTime(const QDateTime &end)
{
    d->end_ = end;
}

QDateTime CompletedClockLine::endTime() const
{
    return d->end_;
}

long CompletedClockLine::duration() const
{
    return startTime().secsTo(d->end_);
}

int CompletedClockLine::durationWithinInterval(const TimeInterval &interval) const
{
    const TimeInterval me(startTime(), endTime());
    const TimeInterval intersection(me.intersection(interval));
    return intersection.duration();
}

bool CompletedClockLine::isElementValid() const
{
    return startTime().isValid() && endTime().isValid() && endTime() >= startTime();
}

QString CompletedClockLine::mnemonic() const
{
    return tr("Clock");
}

QString CompletedClockLine::description() const
{
    auto const seconds = duration();
    return tr("%1:%2 (%3-%4)")
            .arg(seconds / 60)
            .arg(QString::number(seconds % 60), 2, QLatin1Char('0'))
            .arg(startTime().toString())
            .arg(endTime().toString());
}

}
