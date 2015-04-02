#ifndef PARSER_H
#define PARSER_H

#include <QObject>

#include "orgmodeparser_export.h"
#include <OrgElement.h>

class QTextStream;

namespace OrgMode {

class ORGMODEPARSER_EXPORT Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);
    ~Parser();

    OrgElement::Pointer parse(QTextStream* data, const QString& fileName = QString()) const;

private:
    class Private;
    Private* d;
};

QString ORGMODEPARSER_EXPORT version();
}

#endif // PARSER_H
