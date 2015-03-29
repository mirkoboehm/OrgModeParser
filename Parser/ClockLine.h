#ifndef INCOMPLETECLOCKLINE_H
#define INCOMPLETECLOCKLINE_H

#include <QCoreApplication>
#include <QDateTime>
#include <OrgElement.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT ClockLine : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(ClockLine)
public:
    typedef QSharedPointer<ClockLine> Pointer;

    explicit ClockLine(const QString& line, OrgElement* parent = 0);
    explicit ClockLine(OrgElement* parent = 0);

    void setStartTime(const QDateTime& start);
    QDateTime startTime() const;

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
