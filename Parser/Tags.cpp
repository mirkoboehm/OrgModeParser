#include "Tags.h"
#include <Exception.h>

namespace OrgMode {

Tags::Tags(Headline::Pointer element)
{
}

bool Tags::hasTag(QString tag) const
{
    throw NotImplementedException(QLatin1String("NI"));
}

}
