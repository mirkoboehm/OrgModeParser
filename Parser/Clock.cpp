#include <Exception.h>

#include "Clock.h"
#include "ClockLine.h"

namespace OrgMode {

class Clock::Private {
public:
    int subduration(OrgElement::Pointer element);
    OrgElement::Pointer element_;
};

Clock::Clock(OrgElement::Pointer element)
    : d(new Private)
{
    d->element_ = element;
}

int Clock::duration() const
{
    return d->subduration(d->element_);
}

int Clock::Private::subduration(OrgElement::Pointer element)
{
    int subtotal = 0;
    ClockLine* clockLine = dynamic_cast<ClockLine*>(element.data());
    if (clockLine) {
        subtotal += clockLine->duration();
    }
    for (auto child : element->children()) {
        subtotal += subduration(child);
    }
    return subtotal;
}

}
