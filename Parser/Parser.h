#ifndef PARSER_H
#define PARSER_H

#include <QObject>

#include "orgmodeparser_export.h"
#include <Headline.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);
    Headline::Pointer parse() const;
};

}

#endif // PARSER_H
