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

}
