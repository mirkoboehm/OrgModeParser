#ifndef PROPERTYDRAWERENTRY_H
#define PROPERTYDRAWERENTRY_H

#include <QCoreApplication>

#include <DrawerEntry.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT PropertyDrawerEntry : public DrawerEntry
{
    Q_DECLARE_TR_FUNCTIONS(PropertyDrawerEntry)
public:
    typedef QSharedPointer<PropertyDrawerEntry> Pointer;

    explicit PropertyDrawerEntry(OrgElement* parent = 0);
    explicit PropertyDrawerEntry(const QString& line, OrgElement* parent = 0);
    ~PropertyDrawerEntry();

protected:
    QString mnemonic() const override;

private:
    class Private;
    Private* d;
};

}

#endif // PROPERTYDRAWERENTRY_H
