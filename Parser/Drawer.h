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
#ifndef DRAWER_H
#define DRAWER_H

#include <memory>

#include <QCoreApplication>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT Drawer : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(Drawer)
public:
    typedef QSharedPointer<Drawer> Pointer;

    explicit Drawer(OrgElement* parent = nullptr);
    explicit Drawer(const QString& line, OrgElement* parent = nullptr);

    Drawer(Drawer&&);
    Drawer& operator=(Drawer&&);
    ~Drawer() override;

    QString name() const;
    void setName(const QString& name);

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    struct Private;
    std::unique_ptr<Private> d;
};

}

#endif // DRAWER_H
