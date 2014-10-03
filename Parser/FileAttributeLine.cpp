#include "FileAttributeLine.h"

namespace OrgMode {

class FileAttributeLine::Private {
public:
};

FileAttributeLine::FileAttributeLine(OrgMode::OrgElement *parent)
    : FileAttributeLine(QString(), parent)
{
}

FileAttributeLine::FileAttributeLine(const QString &line, OrgElement *parent)
    : AttributeLine(line, parent)
    , d(new Private)
{
}

FileAttributeLine::~FileAttributeLine()
{
    delete d; d = 0;
}

QString FileAttributeLine::mnemonic() const
{
    return tr("FileAttr");
}

}
