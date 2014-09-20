#include <QtDebug>

#include "OrgElement.h"

namespace OrgMode {

class OrgElement::Private {
public:
    Private(OrgElement* parent)
        : parent_(parent)
    {}
    OrgElement::List children_;
    OrgElement* parent_;
    QString line_;
};

OrgElement::OrgElement(const QString &line, OrgElement *parent)
    : OrgElement(parent)
{
    setLine(line);
}

OrgElement::OrgElement(OrgElement* parent)
    : d(new Private(parent))
{
}

OrgElement::~OrgElement()
{
    delete d; d = 0;
}

bool OrgElement::isValid() const
{
    return isElementValid();
}

void OrgElement::setParent(OrgElement* parent)
{
    d->parent_ = parent;
}

OrgElement* OrgElement::parent() const
{
    return d->parent_;
}

QString OrgElement::line() const
{
    return d->line_;
}

void OrgElement::setLine(const QString &line)
{
    d->line_ = line;
}

OrgElement::List OrgElement::children() const
{
    return d->children_;
}

void OrgElement::addChild(const OrgElement::Pointer &child)
{
    child->setParent(this);
    d->children_.append(child);
}

void OrgElement::setChildren(const OrgElement::List &children)
{
    for(auto child : children) {
        child->setParent(this);
    }
    d->children_ = children;
}

int OrgElement::level() const
{
    if (d->parent_) {
        return d->parent_->level() + 1;
    } else {
        return 0;
    }
}

QString OrgElement::describe() const
{
    Q_ASSERT(mnemonic().length() > 0 && mnemonic().length() <=8);
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
