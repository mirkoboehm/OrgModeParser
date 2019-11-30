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

Tags::Tags(Tags && other) = default;
Tags& Tags::operator=(Tags &&other) = default;
Tags::~Tags() = default;

/** @brief hasTag checks if the element is tagged with the specified key.
 *
 * @return true if the element is tagged "tag", directly or inherited from a parent
 */
bool Tags::hasTag(const QString &tag) const
{
    return d->isTagged(d->element_.data(), tag);
}

}
