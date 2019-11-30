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
#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <memory>

#include <QCoreApplication>

#include "orgmodeparser_export.h"
#include <OrgElement.h>
#include <Attributes.h>

namespace OrgMode {

/** @brief The Properties class calculates the values of file attributes and properties for an element.
 *
 * It handles attributes and properties because they are syntactially the same, based on file attributes
 * and drawers. Properties are file attributes and drawers with special names.
 *
 * See http://orgmode.org/manual/Property-syntax.html. The OrgModePropertiesExample.org resource emulates the
 * examples from the OrgMode manual and verifies with unit tests that the results are as expected.
 */
class ORGMODEPARSER_EXPORT Properties
{
    Q_DECLARE_TR_FUNCTIONS(Properties)
public:
    typedef QVector<Property> Vector;

    explicit Properties(const OrgElement::Pointer& element);
    Properties(const Properties&) = delete;
    Properties& operator=(const Properties&);
    Properties(Properties&&);
    Properties& operator=(Properties&&);
    virtual ~Properties();

    QString property(const QString&) const;
    Vector properties() const;

    Vector drawer(const QString& name) const;

    static QString propertyValue(const QString& key, const Vector& definitions);
    static Property parseAttributeAsProperty(const Property& attribute);
private:
    struct Private;
    std::unique_ptr<Private> d;
};

}

#endif // PROPERTIES_H
