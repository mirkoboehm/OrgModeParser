#ifndef CLOCK_H
#define CLOCK_H

#include <QCoreApplication>

#include "orgmodeparser_export.h"
#include <OrgElement.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT Clock
{
    Q_DECLARE_TR_FUNCTIONS(Clock)
public:
    explicit Clock(OrgElement::Pointer element);

    int duration() const;

private:
    class Private;
    Private* d;
};

}

#endif // CLOCK_H
