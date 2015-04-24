#ifndef CLOCK_H
#define CLOCK_H

#include <QCoreApplication>

#include "orgmodeparser_export.h"
#include <OrgElement.h>
#include <TimeInterval.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT Clock
{
    Q_DECLARE_TR_FUNCTIONS(Clock)
public:
    explicit Clock(OrgElement::Pointer element);

    /** Recursively calculate the duration of all clock entries within element's subtree. */
    int duration() const;
    /** Recursively calculate the duration of all clock entries within element's subtree,
     *  bounded by the specified interval. */
    int duration(const TimeInterval& interval) const;
private:
    class Private;
    Private* d;
};

}

#endif // CLOCK_H
