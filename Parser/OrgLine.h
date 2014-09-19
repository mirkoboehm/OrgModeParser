#ifndef ORGLINE_H
#define ORGLINE_H

#include <QCoreApplication>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT OrgLine : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(OrgLine)
public:
    explicit OrgLine(OrgElement* parent = 0);
    explicit OrgLine(const QString& text, OrgElement* parent = 0);
    ~OrgLine();

    void setText(const QString& text);
    QString text() const;

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    class Private;
    Private* d;
};

}

#endif // ORGLINE_H
