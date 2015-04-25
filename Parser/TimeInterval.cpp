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
    //FIXME test!

    return start() <= end() || !start().isValid() || !end().isValid();
}

TimeInterval TimeInterval::intersection(const TimeInterval &other) const
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

int TimeInterval::duration() const
{
    if (!isValid()) return 0;
    if (!start().isValid() || !end().isValid()) return std::numeric_limits<int>::max();
    return start().secsTo(end());
}

bool OrgMode::operator==(const TimeInterval &left, const TimeInterval &right)
{
    return left.start() == right.start() && left.end() == right.end();
}
