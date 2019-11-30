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
#ifndef DRAWERCLOSINGENTRY_H
#define DRAWERCLOSINGENTRY_H

#include <memory>

#include <QCoreApplication>

#include <DrawerEntry.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class DrawerClosingEntry : public DrawerEntry
{
    Q_DECLARE_TR_FUNCTIONS(DrawerClosingEntry)
public:
    typedef QSharedPointer<DrawerClosingEntry> Pointer;

    explicit DrawerClosingEntry(OrgElement* parent = nullptr);
    explicit DrawerClosingEntry(const QString& line, OrgElement* parent = nullptr);
    DrawerClosingEntry(DrawerClosingEntry&&);
    DrawerClosingEntry& operator=(DrawerClosingEntry&&);
    ~DrawerClosingEntry() override;

protected:
    QString mnemonic() const override;

private:
    struct Private;
    std::unique_ptr<Private> d;
};

}

#endif // DRAWERCLOSINGENTRY_H
