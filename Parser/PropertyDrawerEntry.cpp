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

QString PropertyDrawerEntry::description() const
{
    return tr("%1: %2 %3")
            .arg(property().key())
            .arg(property().operation() == Property::Property_Define ? tr("SET") : tr("ADD"))
            .arg(property().value());
}

}
