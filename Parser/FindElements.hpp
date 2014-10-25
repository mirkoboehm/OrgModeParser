#ifndef FINDELEMENTS_HPP
#define FINDELEMENTS_HPP

namespace OrgMode {

static void NilDeleter(OrgElement*) {}

template <typename T, typename Decision>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element, int maxDepth, Decision d) {
    if (!element) return QList<QSharedPointer<T>>();

    QList<QSharedPointer<T>> matches;
    auto const p = element.dynamicCast<T>();
    if (p) {
        const bool decision = d(p);
        if (decision) {
            matches.append(p);
        }
    }
    if (maxDepth == 0) return matches;
    for(auto const child : element->children()) {
        matches.append(findElements<T>(child, maxDepth - 1, d));
    }
    return matches;
}

template <typename T, typename Decision>
QList<QSharedPointer<T>> findElements(OrgElement* element, int maxDepth, Decision d) {
    return findElements<T>(OrgElement::Pointer(element, NilDeleter), maxDepth, d);
}

template <typename T>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element, int maxDepth) {
    auto const decision = [](const QSharedPointer<T>&) { return true; };
    return findElements<T, decltype(decision)>(element, maxDepth, decision);
};

template <typename T>
QList<QSharedPointer<T>> findElements(OrgElement* element, int maxDepth) {
    return findElements<T>(OrgElement::Pointer(element, NilDeleter), maxDepth);
};

template <typename T>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element) {
    return findElements<T>(element, -1);
};

template <typename T>
QList<QSharedPointer<T>> findElements(OrgElement* element) {
    return findElements<T>(OrgElement::Pointer(element, NilDeleter));
};

}

#endif // FINDELEMENTS_HPP
