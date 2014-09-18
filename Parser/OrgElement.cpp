#include <QtDebug>

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

bool OrgElement::isValid() const
{
    return isElementValid();
}

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

void OrgElement::addChild(const OrgElement::Pointer &child)
{
    child->setLevel(level() + 1);
    d->children_.append(child);
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

QString OrgElement::describe() const
{
    QString result = tr("[%1] %2: %3\n")
            .arg(mnemonic(), 8)
            .arg(level(), 3)
            .arg(description());
     for( auto const child : children()) {
         result += child->describe();
     }
    return result;
}

}
