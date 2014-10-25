#include "PropertyDrawerEntry.h"

namespace OrgMode {

class PropertyDrawerEntry::Private {
public:
};

PropertyDrawerEntry::PropertyDrawerEntry(OrgElement *parent)
    : PropertyDrawerEntry(QString(), parent)
{

}

PropertyDrawerEntry::PropertyDrawerEntry(const QString &line, OrgElement *parent)
    : DrawerEntry(line, parent)
    , d(new Private)
{
}

PropertyDrawerEntry::~PropertyDrawerEntry()
{
    delete d; d = 0;
}

QString PropertyDrawerEntry::mnemonic() const
{
    return tr("PrpDEntr");
}

}
