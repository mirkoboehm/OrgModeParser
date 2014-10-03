#include "DrawerEntry.h"

namespace OrgMode {

class DrawerEntry::Private {
public:
};

DrawerEntry::DrawerEntry(OrgMode::OrgElement *parent)
    : DrawerEntry(QString(), parent)
{
}

DrawerEntry::DrawerEntry(const QString &line, OrgMode::OrgElement *parent)
    : OrgElement(line, parent)
    , d(new Private)
{
}

OrgMode::DrawerEntry::~DrawerEntry()
{
    delete d; d = 0;
}

bool OrgMode::DrawerEntry::isElementValid() const
{
    return false; //NI
}

QString OrgMode::DrawerEntry::mnemonic() const
{
    return tr("DrwEntry");
}

QString OrgMode::DrawerEntry::description() const
{
    return tr("NI");
}

}
