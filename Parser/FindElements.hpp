#ifndef FINDELEMENTS_HPP
#define FINDELEMENTS_HPP

namespace OrgMode {

static inline void NilDeleter(OrgElement*) {}

template <typename T, typename Decision>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element, Decision d, int maxDepth) {
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
        matches.append(findElements<T>(child, d, maxDepth - 1));
    }
    return matches;
}

template <typename T, typename Decision>
QList<QSharedPointer<T>> findElements(OrgElement* element, Decision d, int maxDepth) {
    return findElements<T>(OrgElement::Pointer(element, NilDeleter), maxDepth, d);
}

template <typename T>
QList<QSharedPointer<T>> findElements(const OrgElement::Pointer& element, int maxDepth) {
    auto const decision = [](const QSharedPointer<T>&) { return true; };
    return findElements<T, decltype(decision)>(element, decision, maxDepth);
};

template <typename T>
QList<QSharedPointer<T>> findElements(OrgElement* element, int maxDepth) {
    return findElements<T>(OrgElement::Pointer(element, NilDeleter), maxDepth);
};

}

#endif // FINDELEMENTS_HPP
