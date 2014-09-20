#include <Exception.h>

#include "Clock.h"

namespace OrgMode {

class Clock::Private {
public:
    OrgElement::Pointer element_;
};

Clock::Clock(OrgElement::Pointer element)
    : d(new Private)
{
    d->element_ = element;
}

int Clock::duration() const
{
    throw NotImplementedException(tr("NI"));
}

}
