#include <QIODevice>
#include <QTextStream>

#include "Parser.h"
#include "Headline.h"
#include "Exception.h"

namespace OrgMode {

class Parser::Private {
public:
    Private()
        : device_()
    {}
    QIODevice* device_;
};

Parser::Parser(QObject *parent)
    : QObject(parent)
    , d(new Private())
{
}

void Parser::setInputDevice(QIODevice *device)
{
    Q_ASSERT(d);
    Q_ASSERT(d->device_ == 0);
    Q_ASSERT(device->isReadable());
    d->device_ = device;
}

Headline::Pointer Parser::parse() const
{
    Q_ASSERT(d->device_);
    QTextStream stream(d->device_);
    Headline::Pointer toplevel(new Headline());
    toplevel->readFrom(&stream);
    return toplevel;
}

}
