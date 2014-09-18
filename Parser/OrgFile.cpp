#include "OrgFile.h"

namespace OrgMode {

OrgFile::OrgFile()
{
}

bool OrgFile::isElementValid() const
{
    return true;
}

QString OrgFile::mnemonic() const
{
    return QLatin1String("OrgFile");
}

QString OrgFile::description() const
{
    return tr("%1 elements").arg(children().count());
}

}
