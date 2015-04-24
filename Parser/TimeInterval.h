#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include <QDateTime>
#include "orgmodeparser_export.h"

class QDate;

namespace OrgMode {

/** A TimeInterval represents a interval of time that includes start, and excludes end.
 *  In other words, the interval is [start, end[.
 *
 */
class ORGMODEPARSER_EXPORT TimeInterval
{
public:
    explicit TimeInterval(const QDateTime& start_ = QDateTime(), const QDateTime& end_ = QDateTime());
    explicit TimeInterval(const QDate& start_, const QDate& end_);

    /** The start time of the interval. */
    QDateTime start() const;
    /** The end time of the interval. */
    QDateTime end() const;
    /** An interval is valid if start or end are defined. */
    bool isValid() const;
    /** Return the intersection of two intervals.
     *
     * The intersection of two intervals is the common subset of the two intervals.
     * Invalid intervals have no elements, therefore the intersection of any interval with an invalid
     * interval is empty. Invalid and default-constructed intervals are equal.
     */
    TimeInterval intersection(const TimeInterval& other) const;

private:
    class Private;
    Private* d;
};

bool ORGMODEPARSER_EXPORT operator==(const TimeInterval& left, const TimeInterval& right);

}

#endif // TIMEINTERVAL_H
