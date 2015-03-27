#ifndef INCOMPLETECLOCKLINE_H
#define INCOMPLETECLOCKLINE_H

#include <QCoreApplication>

#include <ClockLine.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT IncompleteClockLine : public ClockLine
{
    Q_DECLARE_TR_FUNCTIONS(IncompleteClockLine)
public:
    typedef QSharedPointer<IncompleteClockLine> Pointer;

    explicit IncompleteClockLine(const QString& line, OrgElement* parent = 0);
    explicit IncompleteClockLine(OrgElement* parent = 0);

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    class Private;
    Private* d;
};

}

#endif // INCOMPLETECLOCKLINE_H
