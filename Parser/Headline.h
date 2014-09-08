#ifndef HEADLINE_H
#define HEADLINE_H

#include <QSharedPointer>

#include "orgmodeparser_export.h"

namespace OrgMode {

/** @brief Headline represent a single headline in an OrgMode file. */
class ORGMODEPARSER_EXPORT Headline
{
public:
    typedef QSharedPointer<Headline> Pointer;
    typedef QList<Pointer> List;

    Headline();
    List children() const;
};

}

#endif // HEADLINE_H
