#include "Drawer.h"

namespace OrgMode {

class Drawer::Private {
public:
    QString name_;
};

Drawer::Drawer(OrgElement *parent)
    : Drawer(QString(), parent)
{

}

Drawer::Drawer(const QString &line, OrgElement *parent)
    : OrgLine(line, parent)
    , d(new Private())
{
}

Drawer::~Drawer()
{
    delete d; d = 0;
}

QString Drawer::name() const
{
    return d->name_;
}

void Drawer::setName(const QString &name)
{
    d->name_ = name;
}

bool Drawer::isElementValid() const
{
    return !name().isEmpty();
}

QString Drawer::mnemonic() const
{
    return tr("Drawer");
}

QString Drawer::description() const
{
    return tr(":%1:").arg(name());
}

}
