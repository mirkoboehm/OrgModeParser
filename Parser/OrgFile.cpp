#include "OrgFile.h"

namespace OrgMode {

class OrgFile::Private {
public:
    QString fileName_;
};

OrgFile::OrgFile()
    : d(new Private)
{
}

OrgFile::~OrgFile()
{
    delete d; d = 0;
}

void OrgFile::setFileName(const QString &fileName)
{
    d->fileName_ = fileName;
}

QString OrgFile::fileName() const
{
    return d->fileName_;
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
    return tr("%1 (%2 elements)")
            .arg(fileName().isEmpty() ? tr("<unnamed>") : fileName())
            .arg(children().count());
}

}
