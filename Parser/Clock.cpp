#include <Exception.h>

#include "Clock.h"
#include "CompletedClockLine.h"

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
    CompletedClockLine* clockLine = dynamic_cast<CompletedClockLine*>(element.data());
    if (clockLine) {
        subtotal += clockLine->duration();
    }
    for (auto child : element->children()) {
        subtotal += subduration(child);
    }
    return subtotal;
}

}
