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
#include <QtDebug>
#include <QRegularExpression>

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

OrgElement::OrgElement(OrgElement* parent)
    : d(new Private(parent))
{
}

OrgElement::OrgElement(const QString &line, OrgElement *parent)
    : OrgElement(parent)
{
    setLine(line);
}

OrgElement::OrgElement(OrgElement && other) = default;
OrgElement& OrgElement::operator=(OrgElement &&other) = default;
OrgElement::~OrgElement() = default;

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
     for(auto const& child : children()) {
         result += child->describe();
     }
     return result;
}

bool OrgElement::isMatch(const QRegularExpression &pattern) const
{
    auto const match = pattern.match(line());
    //qDebug() << line() << "matches" << pattern << "?" << (match.hasMatch() ? "yes" : "no");
    return match.hasMatch();
}

}
