#ifndef CLOCKTIMESUMMARY_H
#define CLOCKTIMESUMMARY_H

#include <QObject>
#include <OrgElement.h>

class ClockTimeSummary : public QObject
{
    Q_OBJECT
public:
    explicit ClockTimeSummary(const QStringList& orgfiles, QObject *parent = 0);
    int secondsClockedToday() const;
    int secondsClockedThisWeek() const;

private:
    OrgMode::OrgElement::Pointer toplevel_;
};

#endif // CLOCKTIMESUMMARY_H
