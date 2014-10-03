#ifndef DRAWERENTRY_H
#define DRAWERENTRY_H

#include <QCoreApplication>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT DrawerEntry : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(DrawerEntry)
public:
    explicit DrawerEntry(OrgElement* parent = 0);
    explicit DrawerEntry(const QString& line, OrgElement* parent = 0);
    ~DrawerEntry();

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    class Private;
    Private* d;
};

}

#endif // DRAWERENTRY_H
