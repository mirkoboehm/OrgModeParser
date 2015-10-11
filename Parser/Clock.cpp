/** OrgModeParser - a parser for Emacs Org Mode files, written in C++.
    Copyright (C) 2015 Mirko Boehm

    This file is part of OrgModeParser.
    OrgModeParser is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, version 3 of the
    License.

    OrgModeParser is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the GNU General Public License for more details. You should
    have received a copy of the GNU General Public License along with
    OrgModeParser. If not, see <http://www.gnu.org/licenses/>.
*/
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
