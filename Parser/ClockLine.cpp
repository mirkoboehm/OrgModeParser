#include "ClockLine.h"


namespace OrgMode {

class ClockLine::Private {
public:
    QDateTime end_;
};

ClockLine::ClockLine(const QString &line, OrgElement *parent)
    : IncompleteClockLine(line, parent)
    , d(new Private)
{

}

ClockLine::ClockLine(OrgElement *parent)
    : ClockLine(QString(), parent)
{
}

void ClockLine::setEndTime(const QDateTime &end)
{
    d->end_ = end;
}

QDateTime ClockLine::endTime() const
{
    return d->end_;
}

int ClockLine::duration() const
{
    return startTime().secsTo(d->end_);
}

bool ClockLine::isElementValid() const
{
    return startTime().isValid() && endTime().isValid() && endTime() >= startTime();
}

QString ClockLine::mnemonic() const
{
    return tr("Clock");
}

QString ClockLine::description() const
{
    auto const seconds = duration();
    return tr("%1:%2 (%3-%4)")
            .arg(seconds / 60)
            .arg(QString::number(seconds % 60), 2, QLatin1Char('0'))
            .arg(startTime().toString())
            .arg(endTime().toString());
}

}
