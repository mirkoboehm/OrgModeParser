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
    : AttributeLine(line, parent)
    , d(new Private)
{
}

OrgMode::DrawerEntry::~DrawerEntry()
{
    delete d; d = 0;
}

QString OrgMode::DrawerEntry::mnemonic() const
{
    return tr("DrwEntry");
}

}
