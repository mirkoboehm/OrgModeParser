#include <Exception.h>

#include "Clock.h"
#include "CompletedClockLine.h"

namespace OrgMode {

class Clock::Private {
public:
    int subduration(const TimeInterval & interval, OrgElement::Pointer element);
    OrgElement::Pointer element_;
};

Clock::Clock(OrgElement::Pointer element)
    : d(new Private)
{
    d->element_ = element;
}

int Clock::duration() const
{
    return duration(TimeInterval());
}

int Clock::duration(const TimeInterval& interval) const
{
    return d->subduration(interval, d->element_);
}

int Clock::Private::subduration(const TimeInterval& interval, OrgElement::Pointer element)
{
    int subtotal = 0;
    CompletedClockLine* clockLine = dynamic_cast<CompletedClockLine*>(element.data());
    if (clockLine) {
        subtotal += clockLine->durationWithinInterval(interval);
    }
    for (auto child : element->children()) {
        subtotal += subduration(interval, child);
    }
    return subtotal;
}

}
