#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include <QDateTime>
#include "orgmodeparser_export.h"

class QDate;

namespace OrgMode {

/** A TimeInterval represents a interval of time that includes start, and excludes end.
 *
 * In other words, the interval is [start, end[, provided both times are valid.
 * An invalid start or end time mean the interval is open. An interval where start is
 * equal to end is empty and has no elements. Two intervals are equal if their start
 * and end times are equal.
 *
 * @see QDateTime::isValid()
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
    /** An interval is valid if start is later or equal to end, or at least one of start or end are defined. */
    bool isValid() const;
    /** Return the intersection of two intervals.
     *
     * The intersection of two intervals is the common subset of the two intervals. Here are some
     * examples (assume items are in alphabetical order, a < b:
     *
     * 1) ([a, c[).intersection([b, d[)  = [b, c[
     * 2) ([*, c[).intersection([b, *[)  = [b, c[
     * 3) ([b, *[).intersection([c, *[)  = [c, *[
     *    ([*, b[).intersection([*, c[)  = [*, b[
     * 4) ([a, b[).intersection([c, d[)  = [c, c[
     * 5) ([x, y[).intersection([*, *[)  = [x, y[
     *    ([*, *[).intersection([*, *[)  = [*, *[
     * 6) ([a, b[).intersection([b, c[)  = [b, b[
     *    ([b, c[).intersection([a, b[)  = [b, b[
     * @see ClockTests::testTimeIntervals()
     */
    TimeInterval intersection(const TimeInterval& other) const;

private:
    class Private;
    Private* d;
};

bool ORGMODEPARSER_EXPORT operator==(const TimeInterval& left, const TimeInterval& right);

}

#endif // TIMEINTERVAL_H
