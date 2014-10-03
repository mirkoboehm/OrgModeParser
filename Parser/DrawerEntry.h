#ifndef DRAWERENTRY_H
#define DRAWERENTRY_H

#include <QCoreApplication>

#include <AttributeLine.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT DrawerEntry : public AttributeLine
{
    Q_DECLARE_TR_FUNCTIONS(DrawerEntry)
public:
    typedef QSharedPointer<DrawerEntry> Pointer;

    explicit DrawerEntry(OrgElement* parent = 0);
    explicit DrawerEntry(const QString& line, OrgElement* parent = 0);
    ~DrawerEntry();

protected:
    QString mnemonic() const override;

private:
    class Private;
    Private* d;
};

}

#endif // DRAWERENTRY_H
