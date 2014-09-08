#ifndef PARSER_H
#define PARSER_H

#include <QObject>

#include "orgmodeparser_export.h"
#include <Headline.h>

class QIODevice;

namespace OrgMode {

class ORGMODEPARSER_EXPORT Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);
    void setInputDevice(QIODevice* device);
    Headline::Pointer parse() const;

private:
    class Private;
    Private* d;
};

}

#endif // PARSER_H
