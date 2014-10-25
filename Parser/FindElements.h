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
