#include "Headline.h"
#include "Exception.h"
#include "OrgFileContent.h"

namespace OrgMode {

class Headline::Private {
public:
    QString caption_;
    QStringList lines_;
};

Headline::Headline()
    : d(new Private)
{
}

Headline::~Headline()
{
    delete d; d = 0;
}

QString Headline::caption() const
{
    return d->caption_;
}

void Headline::setCaption(const QString &caption)
{
    d->caption_ = caption;
}

bool Headline::isElementValid() const
{
    return level() > 0;
}

QString Headline::mnemonic() const
{
    return QLatin1String("Headline");
}

QString Headline::description() const
{
    return tr("%1 %3").arg(QString(), level(), QLatin1Char('*')).arg(caption());
}

}
