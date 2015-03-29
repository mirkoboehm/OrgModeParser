#include "ClockLine.h"

namespace OrgMode {

class ClockLine::Private {
public:
    QDateTime start_;
};

ClockLine::ClockLine(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(new Private)
{
}

ClockLine::ClockLine(OrgElement *parent)
    : ClockLine(QString(), parent)
{
}

void ClockLine::setStartTime(const QDateTime &start)
{
    d->start_ = start;
}

QDateTime ClockLine::startTime() const
{
    return d->start_;
}

bool OrgMode::ClockLine::isElementValid() const
{
    return startTime().isValid();
}

QString OrgMode::ClockLine::mnemonic() const
{
    return tr("IncmpClk");
}

QString OrgMode::ClockLine::description() const
{
    return tr("%1-").arg(startTime().toString());
}

}
