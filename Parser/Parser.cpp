#include <QIODevice>
#include <QTextStream>

#include "Parser.h"
#include "OrgElement.h"
#include "Exception.h"
#include "OrgFileContent.h"

namespace OrgMode {

class Parser::Private {
public:
};

Parser::Parser(QObject *parent)
    : QObject(parent)
    , d(new Private())
{
}

Parser::~Parser()
{
    delete d; d = 0;
}

OrgElement::Pointer Parser::parse(QTextStream *data) const
{
    Q_ASSERT(data);
    OrgFileContent content(data);

    //OrgElement::Pointer toplevel(new Headline());
    //toplevel->readFrom(&content);
    return OrgElement::Pointer();
}

}
