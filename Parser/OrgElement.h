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
#ifndef ORGELEMENT_H
#define ORGELEMENT_H

#include <QCoreApplication>
#include <QSharedPointer>
#include <QRegularExpression>

#include "orgmodeparser_export.h"

class QRegularExpression;

namespace OrgMode {

/** @brief OrgElement represents an element of an org mode file.
 *
 * Example elements are headlines, lines of text, and other parts of an org file.
 * Elements are always bound by line breaks.
 */
class ORGMODEPARSER_EXPORT OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(OrgElement)
public:
    typedef QSharedPointer<OrgElement> Pointer;
    typedef QList<Pointer> List;

    explicit OrgElement(const QString& line, OrgElement* parent = nullptr);
    explicit OrgElement(OrgElement* parent = nullptr);
    virtual ~OrgElement();
    bool isValid() const;
    void setParent(OrgElement* parent);
    OrgElement* parent() const;

    QString line() const;
    void setLine(const QString& line);

    List children() const;
    void addChild(const Pointer& child);
    void setChildren(const List& children);

    int level() const;

    QString describe() const;

    virtual bool isMatch(const QRegularExpression& pattern) const;

protected:
    virtual bool isElementValid() const = 0;
    virtual QString mnemonic() const = 0;
    virtual QString description() const = 0;

private:
    class Private;
    Private* d;
};

//FIXME Check if isMatch could be a template specialization for findElements:
template <typename T>
QSharedPointer<T> findElement(OrgElement::Pointer element, const QRegularExpression& pattern) {
    QSharedPointer<T> p = element.dynamicCast<T>();
    if (p && element->isMatch(pattern)) {
        return p;
    } else {
        for(auto child : element->children()) {
            if (QSharedPointer<T> match = findElement<T>(child, pattern)) {
                return match;
            } else {
                //No match, continue
            }
        }
    }
    return QSharedPointer<T>();
}

template <typename T>
QSharedPointer<T> findElement(OrgElement::Pointer element, const QString& pattern) {
    const QRegularExpression re(pattern);
    return findElement<T>(element, re);
}

}

#endif // ORGELEMENT_H
