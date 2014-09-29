#include "Properties.h"
#include "Exception.h"

namespace OrgMode {

Properties::Properties(const OrgElement::Pointer &element)
{
}

QString Properties::property(const QString &)
{
    throw NotImplementedException(tr("NI"));
}

}
