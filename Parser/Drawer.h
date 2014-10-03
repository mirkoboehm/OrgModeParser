#ifndef DRAWER_H
#define DRAWER_H

#include <QCoreApplication>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class Drawer : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(Drawer)
public:
    explicit Drawer(OrgElement* parent = 0);
    explicit Drawer(const QString& line, OrgElement* parent = 0);
    ~Drawer();

    QString name() const;
    void setName(const QString& name);

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    class Private;
    Private* d;
};

}

#endif // DRAWER_H
