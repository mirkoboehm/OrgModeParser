#include "OrgLine.h"

namespace OrgMode {

OrgLine::OrgLine(OrgElement *parent)
    : OrgLine(QString(), parent)
{
}

OrgLine::OrgLine(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(0)
{
}

OrgLine::~OrgLine()
{
}

bool OrgLine::isElementValid() const
{
    return !line().isNull(); // an empty string is not null
}

QString OrgLine::mnemonic() const
{
    return QLatin1String("OrgLine");
}

QString OrgLine::description() const
{
    return tr("%1").arg(line());
}

}
