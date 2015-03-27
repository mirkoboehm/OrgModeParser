#include "IncompleteClockLine.h"

namespace OrgMode {

IncompleteClockLine::IncompleteClockLine(const QString &line, OrgElement *parent)
    : ClockLine(line, parent)
    , d(0)
{
}

IncompleteClockLine::IncompleteClockLine(OrgElement *parent)
    : IncompleteClockLine(QString(), parent)
{
}

bool OrgMode::IncompleteClockLine::isElementValid() const
{
    return startTime().isValid();
}

QString OrgMode::IncompleteClockLine::mnemonic() const
{
    return tr("IncmpClk");
}

QString OrgMode::IncompleteClockLine::description() const
{
    return tr("%1-").arg(startTime().toString());
}

}
