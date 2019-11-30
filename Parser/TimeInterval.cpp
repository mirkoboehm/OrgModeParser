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
#include <limits>

#include <QtDebug>
#include <QDateTime>

#include "TimeInterval.h"
#include "orgmodeparser_export.h"

using namespace OrgMode;

class TimeInterval::Private {
public:
    Private(const QDateTime& start_, const QDateTime& end_)
        : start(start_)
        , end(end_)
    {}

    QDateTime start;
    QDateTime end;
};


TimeInterval::TimeInterval(const QDateTime& start_, const QDateTime& end_)
    : d(new Private(start_, end_))
{
}

TimeInterval::TimeInterval(const QDate &start_, const QDate &end_)
    : TimeInterval(QDateTime(start_), QDateTime(end_))
{
}

TimeInterval::TimeInterval(const TimeInterval& other)
    : TimeInterval()
{
    *d = *(other.d);
}

TimeInterval::TimeInterval(TimeInterval && other) = default;
TimeInterval& TimeInterval::operator=(TimeInterval &&other) = default;
TimeInterval::~TimeInterval() = default;

QDateTime TimeInterval::start() const
{
    return d->start;
}

QDateTime TimeInterval::end() const
{
    return d->end;
}

bool TimeInterval::isValid() const
{
    return start() <= end() || !start().isValid() || !end().isValid();
}

TimeInterval TimeInterval::intersection(const OrgMode::TimeInterval &other) const
{
    if (other == TimeInterval()) return *this;
    if (*this == TimeInterval()) return other;

    const QDateTime s(qMax(start().isValid() ? start() : other.start(),
                           other.start().isValid() ? other.start() : start()));
    const QDateTime e(qMin(end().isValid() ? end() : other.end(),
                           other.end().isValid() ? other.end() : end()));

    const QDateTime eLowerBound = e.isValid() ? qMax(e, s) : e;
    return TimeInterval(s, eLowerBound);
}

long TimeInterval::duration() const
{
    if (!isValid()) return 0;
    if (!start().isValid() || !end().isValid()) return std::numeric_limits<int>::max();
    return start().secsTo(end());
}

bool OrgMode::operator==(const TimeInterval &left, const OrgMode::TimeInterval &right)
{
    return left.start() == right.start() && left.end() == right.end();
}
