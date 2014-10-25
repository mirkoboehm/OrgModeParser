#include "PropertyDrawer.h"

namespace OrgMode {

class PropertyDrawer::Private {
public:
};

PropertyDrawer::PropertyDrawer(OrgElement *parent)
    : PropertyDrawer(QString(), parent)
{
}

PropertyDrawer::PropertyDrawer(const QString &line, OrgElement *parent)
    : Drawer(line, parent)
    , d(new Private())
{
}

PropertyDrawer::~PropertyDrawer()
{
    delete d; d = 0;
}

QString PropertyDrawer::mnemonic() const
{
    return tr("PropDrwr");
}

}
