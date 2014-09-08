#include "Headline.h"
#include "Exception.h"

namespace OrgMode {

Headline::Headline()
{
}

Headline::List Headline::children() const
{
    return List(); //TODO NI
}

void Headline::readFrom(QTextStream *device)
{
    throw NotImplementedException(tr("not implemented"));
}

}
