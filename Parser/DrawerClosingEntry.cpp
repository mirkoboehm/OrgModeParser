#include "DrawerClosingEntry.h"

namespace OrgMode {

class DrawerClosingEntry::Private {
public:
};

DrawerClosingEntry::DrawerClosingEntry(OrgMode::OrgElement *parent)
    : DrawerEntry(QString(), parent)
{
}

DrawerClosingEntry::DrawerClosingEntry(const QString &line, OrgMode::OrgElement *parent)
    : DrawerEntry(line, parent)
    , d(new Private)
{

}

DrawerClosingEntry::~DrawerClosingEntry()
{
    delete d; d = 0;
}

QString DrawerClosingEntry::mnemonic() const
{
    return tr("DrwClose");
}

}
