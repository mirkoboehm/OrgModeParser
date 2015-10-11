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

#include "Headline.h"
#include "Exception.h"
#include "OrgFileContent.h"

namespace OrgMode {

class Headline::Private {
public:
    QString caption_;
    QStringList lines_;
    Headline::Tags tags_;
};

Headline::Headline(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(new Private)
{

}

Headline::Headline(OrgElement* parent)
    : OrgElement(parent)
    , d(new Private)
{
}

Headline::~Headline()
{
    delete d; d = 0;
}

QString Headline::caption() const
{
    return d->caption_;
}

void Headline::setCaption(const QString &caption)
{
    d->caption_ = caption;
}

Headline::Tags Headline::tags() const
{
    return d->tags_;
}

void Headline::setTags(const Headline::Tags &tags)
{
    d->tags_ = tags;
}

bool Headline::isElementValid() const
{
    return level() > 0;
}

QString Headline::mnemonic() const
{
    return QLatin1String("Headline");
}

QString Headline::description() const
{
    return tr("%1 %3").arg(QString(), level(), QLatin1Char('*')).arg(caption());
}

bool Headline::isMatch(const QRegularExpression &pattern) const
{
    auto const match = pattern.match(caption());
    //qDebug() << caption() << "matches" << pattern << "?" << (match.hasMatch() ? "yes" : "no");
    return match.hasMatch();
}

}
