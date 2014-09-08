#include "Parser.h"

namespace OrgMode {

Parser::Parser(QObject *parent) :
    QObject(parent)
{
}

Headline::Pointer Parser::parse() const
{
    throw std::runtime_error("not implemented");
}

}
