#ifndef DRAWERCLOSINGENTRY_H
#define DRAWERCLOSINGENTRY_H

#include <QCoreApplication>

#include <DrawerEntry.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class DrawerClosingEntry : public DrawerEntry
{
    Q_DECLARE_TR_FUNCTIONS(DrawerClosingEntry)
public:
    typedef QSharedPointer<DrawerClosingEntry> Pointer;

    explicit DrawerClosingEntry(OrgElement* parent = 0);
    explicit DrawerClosingEntry(const QString& line, OrgElement* parent = 0);
    ~DrawerClosingEntry();

protected:
    QString mnemonic() const override;

private:
    class Private;
    Private* d;
};

}

#endif // DRAWERCLOSINGENTRY_H
