#ifndef FINDELEMENTS_H
#define FINDELEMENTS_H

#include <QList>
#include <QSharedPointer>

#include <OrgElement.h>

namespace OrgMode {

//FIXME Should this return an "Agenda" that is an OrgElement?
//The advantage would be that the result could be used in algorithms again.
template <typename T, typename Decision>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element, int maxDepth, Decision d);

template <typename T>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element, int maxDepth);

}

#include <FindElements.hpp>

#endif // FINDELEMENTS_H
