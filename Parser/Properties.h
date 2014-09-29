#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QCoreApplication>

#include "orgmodeparser_export.h"
#include <OrgElement.h>

namespace OrgMode {

class ORGMODEPARSER_EXPORT Properties
{
    Q_DECLARE_TR_FUNCTIONS(Properties)
public:
    explicit Properties(const OrgElement::Pointer& element);
    QString property(const QString&);
};

}

#endif // PROPERTIES_H
