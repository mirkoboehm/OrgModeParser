#include "ClockLine.h"


namespace OrgMode {

class ClockLine::Private {
public:
    QDateTime start_;
    QDateTime end_;
};

ClockLine::ClockLine(const QString &line, OrgElement *parent)
    : OrgElement(line, parent)
    , d(new Private)
{

}

ClockLine::ClockLine(OrgElement *parent)
    : OrgElement(QString(), parent)
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
    return d->start_.secsTo(d->end_);
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
