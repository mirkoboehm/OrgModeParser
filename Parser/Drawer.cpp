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
#include "Drawer.h"

namespace OrgMode {

class Drawer::Private {
public:
    QString name_;
};

Drawer::Drawer(OrgElement *parent)
    : Drawer(QString(), parent)
{
}

Drawer::Drawer(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(new Private())
{
}

Drawer::Drawer(Drawer && other) = default;
Drawer& Drawer::operator=(Drawer &&other) = default;
Drawer::~Drawer() = default;

QString Drawer::name() const
{
    return d->name_;
}

void Drawer::setName(const QString &name)
{
    d->name_ = name;
}

bool Drawer::isElementValid() const
{
    return !name().isEmpty();
}

QString Drawer::mnemonic() const
{
    return tr("Drawer");
}

QString Drawer::description() const
{
    return tr(":%1:").arg(name());
}

}
