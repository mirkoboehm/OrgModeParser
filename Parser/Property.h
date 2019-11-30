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
#ifndef PROPERTY_H
#define PROPERTY_H

#include <QMetaType>
#include <memory>

#include <QString>

#include "orgmodeparser_export.h"

namespace OrgMode {

/** @brief A helper to handle key-value properties.
 */
class ORGMODEPARSER_EXPORT Property {
public:
    enum Operation {
        Property_Define,
        Property_Add
    };

    Property();
    explicit Property(const QString& key, const QString& value, Operation op = Property_Define);
    Property(const Property& other);
    Property& operator=(const Property&);

    Property(Property&&);
    Property& operator=(Property&&);
    ~Property();

    bool operator==(const Property& other) const;

    bool isValid() const;
    void apply(const Property& token);

    QString key() const;
    void setKey(const QString& key);

    QString value() const;
    void setValue(const QString& value) const;

    Operation operation() const;
    void setOperation(Operation op);

private:
    class Private;
    std::unique_ptr<Private> d;
};

}

Q_DECLARE_METATYPE(OrgMode::Property)

#endif // PROPERTY_H
