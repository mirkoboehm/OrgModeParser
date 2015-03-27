#include "IncompleteClockLine.h"

namespace OrgMode {

class IncompleteClockLine::Private {
public:
    QDateTime start_;
};

IncompleteClockLine::IncompleteClockLine(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(new Private)
{
}

IncompleteClockLine::IncompleteClockLine(OrgElement *parent)
    : IncompleteClockLine(QString(), parent)
{
}

void IncompleteClockLine::setStartTime(const QDateTime &start)
{
    d->start_ = start;
}

QDateTime IncompleteClockLine::startTime() const
{
    return d->start_;
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
