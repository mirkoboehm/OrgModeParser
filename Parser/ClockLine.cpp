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
#include "ClockLine.h"

namespace OrgMode {

class ClockLine::Private {
public:
    QDateTime start_;
};

ClockLine::ClockLine(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(new Private)
{
}

ClockLine::ClockLine(ClockLine && other) = default;
ClockLine& ClockLine::operator=(ClockLine &&other) = default;
ClockLine::~ClockLine() = default;

ClockLine::ClockLine(OrgElement *parent)
    : ClockLine(QString(), parent)
{
}

void ClockLine::setStartTime(const QDateTime &start)
{
    d->start_ = start;
}

QDateTime ClockLine::startTime() const
{
    return d->start_;
}

bool OrgMode::ClockLine::isElementValid() const
{
    return startTime().isValid();
}

QString OrgMode::ClockLine::mnemonic() const
{
    return tr("IncmpClk");
}

QString OrgMode::ClockLine::description() const
{
    return tr("%1-").arg(startTime().toString());
}

}
