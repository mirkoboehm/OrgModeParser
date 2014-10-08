#include <QtDebug>
#include <QMap>

#include <Properties.h>
#include <FileAttributeLine.h>
#include <Exception.h>
#include <OrgFile.h>
#include <Drawer.h>
#include <DrawerEntry.h>
#include <FindElements.h>

namespace OrgMode {

class Properties::Private {
public:
    explicit Private(const OrgElement::Pointer &element)
        : element_(element)
    {}
    OrgElement::Pointer element_;
};

template <typename T>
T* findNextHigherUp(OrgElement* element) {
    if (!element) return 0;
    T* p = dynamic_cast<T*>(element);
    if (p) {
        return p;
    } else if (element->parent()) {
        return findNextHigherUp<T>(element->parent());
    } else {
        return 0;
    }
}

static void NilDeleter(OrgElement*) {}

Properties::Properties(const OrgElement::Pointer &element)
    : d(new Private(element))
{
}

Properties::~Properties()
{
    delete d; d = 0;
}

QString Properties::property(const QString& key) const
{
    throw NotImplementedException();
}

Properties::Map Properties::properties() const
{
    throw NotImplementedException();
}

QString Properties::fileAttribute(const QString &key) const
{
    const Map attributes(fileAttributes());
    Map::const_iterator it = attributes.find(key);
    if (it != attributes.end()) {
        return it.value();
    } else {
        return QString();
    }
}


Properties::Map Properties::drawer(const QString &name) const
{
    auto const decision = [name](const Drawer::Pointer& drawer) -> bool {
        return name == drawer->name();
    };
    auto const drawers = findElements<Drawer>(d->element_, 1, decision);
    if (drawers.isEmpty()) {
        throw RuntimeException(tr("No drawer named %1 found!").arg(name));
    }
    auto const drawer = drawers.first();
    auto const entryElements = findElements<DrawerEntry>(drawer, 1);
    Map entries;
    std::for_each(entryElements.begin(), entryElements.end(),
                  [&entries](const DrawerEntry::Pointer& entry) {
        entries.insert(entry->key(), entry->value());
    } );
    return entries;
}

Properties::Map Properties::fileAttributes() const
{
    //Find an OrgFile element that is the parent of this one. If there isn't any, no problem, continue.
    //If there is, query its property values and add it to the map as the default for the element
    //local properties:
    auto const file = findNextHigherUp<OrgFile>(d->element_.data());
    QSharedPointer<OrgFile> pf(file, NilDeleter);
    Map p;
    if (file) {
        auto const fileAttributes = findElements<FileAttributeLine>(pf);
        for(auto const attribute : fileAttributes) {
            p.insert(attribute->key(), attribute->value());
        }
    }
    return p;
}

}
