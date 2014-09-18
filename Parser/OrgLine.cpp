#include "OrgLine.h"

namespace OrgMode {

class OrgLine::Private {
public:
    QString line_;
};

OrgLine::OrgLine()
    : d(new Private())
{
}

OrgLine::OrgLine(const QString &text)
    : OrgLine()
{
    d->line_ = text;
}

OrgLine::~OrgLine()
{
    delete d; d = 0;
}

void OrgLine::setText(const QString &text)
{
    d->line_ = text;
}

QString OrgLine::text() const
{
    return d->line_;
}

bool OrgLine::isElementValid() const
{
    return !d->line_.isNull(); // an empty string is not null
}

QString OrgLine::mnemonic() const
{
    return QLatin1String("OrgLine");
}

QString OrgLine::description() const
{
    return tr("%1").arg(text());
}

}
