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
#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QCoreApplication>
#include <QVector>

#include "orgmodeparser_export.h"
#include <Property.h>
#include <OrgElement.h>

namespace OrgMode {

/** @brief Attributes handles file attributes for an OrgElement.
 *
 * File attributes are notated in "#+ATTRIBUTE:" syntax. They are used to specify the author or title of a
 * document.
 * Properties are a special type of attributes that can be inherited and manipulated while the element tree
 * is traversed.
 */
class ORGMODEPARSER_EXPORT Attributes
{
    Q_DECLARE_TR_FUNCTIONS(Attributes)
public:
    typedef QVector<Property> Vector;

    explicit Attributes(const OrgElement::Pointer& element);
    ~Attributes();


    QString fileAttribute(const QString& key) const;
    Vector fileAttributes(const QString& key) const;
    Vector fileAttributes() const;

    const QStringList drawerNames() const;

    static QString attribute(const Vector& attributes, const QString& key);

private:
    class Private;
    Private* d;
};

}

#endif // ATTRIBUTES_H
