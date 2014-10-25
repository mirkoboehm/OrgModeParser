#ifndef PROPERTYDRAWER_H
#define PROPERTYDRAWER_H

#include <QCoreApplication>

#include <Drawer.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT PropertyDrawer : public Drawer
{
    Q_DECLARE_TR_FUNCTIONS(PropertyDrawer)
public:
    typedef QSharedPointer<Drawer> Pointer;

    explicit PropertyDrawer(OrgElement* parent = 0);
    explicit PropertyDrawer(const QString& line, OrgElement* parent = 0);
    ~PropertyDrawer();

protected:
    QString mnemonic() const override;

private:
    class Private;
    Private* d;
};

}

#endif // PROPERTYDRAWER_H
