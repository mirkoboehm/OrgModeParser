#include "Tags.h"
#include <Exception.h>

namespace OrgMode {

class Tags::Private {
public:
    Private(const Headline::Pointer& element)
        : element_(element)
    {}

    Headline::Pointer element_;

    bool isTagged(Headline* element, const QString& tag);
};

bool Tags::Private::isTagged(Headline *element, const QString &tag)
{
    auto const tags = element->tags();
    auto const it = std::find(tags.begin(), tags.end(), tag);
    if (it != tags.end()) {
        return true;
    } else {
        Headline* const parent = dynamic_cast<Headline*>(element->parent());
        if (parent) {
            return isTagged(parent, tag);
        } else {
            return false;
        }
    }
}

Tags::Tags(const Headline::Pointer& element)
    : d(new Private(element))
{
}


/** @brief hasTag checks if the element is tagged with the specified key.
 *
 * @return true if the element is tagged "tag", directly or inherited from a parent
 */
bool Tags::hasTag(const QString &tag) const
{
    return d->isTagged(d->element_.data(), tag);
}

}
