#ifndef CLOCKLINE_H
#define CLOCKLINE_H

#include <QCoreApplication>
#include <QDateTime>

#include <IncompleteClockLine.h>

#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT CompletedClockLine : public IncompleteClockLine
{
    Q_DECLARE_TR_FUNCTIONS(ClockLine)
public:
    typedef QSharedPointer<CompletedClockLine> Pointer;

    explicit CompletedClockLine(const QString& line, OrgElement* parent = 0);
    explicit CompletedClockLine(OrgElement* parent = 0);

    void setEndTime(const QDateTime& end);
    QDateTime endTime() const;

    int duration() const;

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    class Private;
    Private* d;
};

}

#endif // CLOCKLINE_H
