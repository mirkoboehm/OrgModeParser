#include "FileAttributeLine.h"

namespace OrgMode {

class FileAttributeLine::Private {
public:
    QString key_;
    QString value_;
};

FileAttributeLine::FileAttributeLine(OrgMode::OrgElement *parent)
    : FileAttributeLine(QString(), parent)
{
}

FileAttributeLine::FileAttributeLine(const QString &line, OrgElement *parent)
    : OrgLine(line, parent)
    , d(new Private)
{
}

FileAttributeLine::~FileAttributeLine()
{
    delete d; d = 0;
}

void FileAttributeLine::setProperty(const QString &key, const QString &value)
{
    d->key_ = key;
    d->value_ = value;
}

QString FileAttributeLine::key() const
{
    return d->key_;
}

QString FileAttributeLine::value() const
{
    return d->value_;
}

bool FileAttributeLine::isElementValid() const
{
    return !d->key_.isEmpty() && !d->value_.isEmpty();
}

QString FileAttributeLine::mnemonic() const
{
    return tr("FileAttr");
}

QString FileAttributeLine::description() const
{
    return tr("%1: %2").arg(d->key_).arg(d->value_);
}

}
