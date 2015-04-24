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
