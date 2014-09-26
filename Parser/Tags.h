#ifndef TAGS_H
#define TAGS_H

#include <QCoreApplication>

#include "orgmodeparser_export.h"
#include <Headline.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT Tags
{
public:
    Tags(Headline::Pointer element);
    bool hasTag(QString tag) const;

private:
    class Private;
    Private* d;
};

}

#endif // TAGS_H
