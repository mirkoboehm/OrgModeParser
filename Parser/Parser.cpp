#include <QIODevice>
#include <QTextStream>

#include "Parser.h"
#include "Headline.h"
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

Headline::Pointer Parser::parse(QTextStream *data) const
{
    Q_ASSERT(data);
    OrgFileContent content(data);
    Headline::Pointer toplevel(new Headline());
    toplevel->readFrom(&content);
    return toplevel;
}

}
