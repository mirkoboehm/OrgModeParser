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
#ifndef FINDELEMENTS_H
#define FINDELEMENTS_H

#include <QList>
#include <QSharedPointer>

#include <OrgElement.h>

namespace OrgMode {

//FIXME Should this return an "Agenda" that is an OrgElement?
//The advantage would be that the result could be used in algorithms again.

/** @brief Find all elements of a specific type, starting from element, up to maxDepth edges deep, where decision returns true.
  *
  * To search for all kinds of OrgMode elements, use OrgElement as the type to search for.
  */
template <typename T, typename Decision>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element, int maxDepth, Decision d);

/** @brief Find all elements of a specific type, starting from element, up to maxDepth edges deep, where decision returns true.
  *
  * To search for all kinds of OrgMode elements, use OrgElement as the type to search for.
  */
template <typename T, typename Decision>
QList<QSharedPointer<T>> findElements(OrgElement*, int maxDepth, Decision d);

/** @brief Find all elements of a specific type, starting from element, up to maxDepth edges deep. */
template <typename T>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element, int maxDepth);

/** @brief Find all elements of a specific type, starting from element. */
template <typename T>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element);

/** @brief Find all elements of a specific type, starting from element, up to maxDepth edges deep. */
template <typename T>
QList<QSharedPointer<T>> findElements(OrgElement* element, int maxDepth);

/** @brief Find all elements of a specific type, starting from element. */
template <typename T>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element);

/** @brief Find all elements of a specific type, starting from element. */
template <typename T>
QList<QSharedPointer<T>> findElements(OrgElement* element);

}

#include <FindElements.hpp>

#endif // FINDELEMENTS_H
