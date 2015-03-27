#ifndef INCOMPLETECLOCKLINE_H
#define INCOMPLETECLOCKLINE_H

#include <QCoreApplication>
#include <QDateTime>
#include <OrgElement.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT IncompleteClockLine : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(IncompleteClockLine)
public:
    typedef QSharedPointer<IncompleteClockLine> Pointer;

    explicit IncompleteClockLine(const QString& line, OrgElement* parent = 0);
    explicit IncompleteClockLine(OrgElement* parent = 0);

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
