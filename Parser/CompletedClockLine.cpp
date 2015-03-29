#include "CompletedClockLine.h"

namespace OrgMode {

class CompletedClockLine::Private {
public:
    QDateTime end_;
};

CompletedClockLine::CompletedClockLine(const QString &line, OrgElement *parent)
    : IncompleteClockLine(line, parent)
    , d(new Private)
{

}

CompletedClockLine::CompletedClockLine(OrgElement *parent)
    : CompletedClockLine(QString(), parent)
{
}

void CompletedClockLine::setEndTime(const QDateTime &end)
{
    d->end_ = end;
}

QDateTime CompletedClockLine::endTime() const
{
    return d->end_;
}

int CompletedClockLine::duration() const
{
    return startTime().secsTo(d->end_);
}

bool CompletedClockLine::isElementValid() const
{
    return startTime().isValid() && endTime().isValid() && endTime() >= startTime();
}

QString CompletedClockLine::mnemonic() const
{
    return tr("Clock");
}

QString CompletedClockLine::description() const
{
    auto const seconds = duration();
    return tr("%1:%2 (%3-%4)")
            .arg(seconds / 60)
            .arg(QString::number(seconds % 60), 2, QLatin1Char('0'))
            .arg(startTime().toString())
            .arg(endTime().toString());
}

}
