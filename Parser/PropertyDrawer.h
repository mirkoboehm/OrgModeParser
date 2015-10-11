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
#ifndef PROPERTYDRAWER_H
#define PROPERTYDRAWER_H

#include <QCoreApplication>

#include <Drawer.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT PropertyDrawer : public Drawer
{
    Q_DECLARE_TR_FUNCTIONS(PropertyDrawer)
public:
    typedef QSharedPointer<PropertyDrawer> Pointer;

    explicit PropertyDrawer(OrgElement* parent = 0);
    explicit PropertyDrawer(const QString& line, OrgElement* parent = 0);
    ~PropertyDrawer();

protected:
    QString mnemonic() const override;

private:
    class Private;
    Private* d;
};

}

#endif // PROPERTYDRAWER_H
