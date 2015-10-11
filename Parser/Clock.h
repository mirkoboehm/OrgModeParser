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

    /** Recursively calculate the duration of all clock entries within element's subtree,
     *  bounded by the specified interval. */
    int duration(const TimeInterval& interval = TimeInterval()) const;
private:
    class Private;
    Private* d;
};

}

#endif // CLOCK_H
