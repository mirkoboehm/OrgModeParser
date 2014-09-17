#include "OrgElement.h"

namespace OrgMode {

class OrgElement::Private {
public:
    Private()
        : level_()
    {}
    OrgElement::List children_;
    int level_;
};

OrgElement::OrgElement()
    : d(new Private())
{
}

OrgElement::~OrgElement()
{
    delete d; d = 0;
}

OrgElement::List OrgElement::children() const
{
    return d->children_;
}

void OrgElement::setChildren(const OrgElement::List &children)
{
    d->children_ = children;
}

int OrgElement::level() const
{
    return d->level_;
}

void OrgElement::setLevel(int level)
{
    d->level_ = level;
}

}
