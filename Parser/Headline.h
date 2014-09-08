#ifndef HEADLINE_H
#define HEADLINE_H

#include <QCoreApplication>
#include <QSharedPointer>

#include "orgmodeparser_export.h"

class QTextStream;

namespace OrgMode {

/** @brief Headline represent a single headline in an OrgMode file. */
class ORGMODEPARSER_EXPORT Headline
{
    Q_DECLARE_TR_FUNCTIONS(Headline)
public:
    typedef QSharedPointer<Headline> Pointer;
    typedef QList<Pointer> List;

    Headline();
    List children() const;

    void readFrom(QTextStream* device);
};

}

#endif // HEADLINE_H
