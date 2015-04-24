#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include <QDateTime>
#include "orgmodeparser_export.h"

class QDate;

namespace OrgMode {

/** A TimeInterval represents a interval of time that includes start, and excludes end.
 *  In other words, the interval is [start, end[.
 *
 *
 */
class ORGMODEPARSER_EXPORT TimeInterval
{
public:
    explicit TimeInterval(const QDateTime& start_ = QDateTime(), const QDateTime& end_ = QDateTime());
    explicit TimeInterval(const QDate& start_, const QDate& end_);

private:
    class Private;
    Private* d;
};

}

#endif // TIMEINTERVAL_H
