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
    typedef QMap<QString, QString> PropertiesMap;

    explicit Properties(const OrgElement::Pointer& element);
    QString property(const QString&) const;
    PropertiesMap properties() const;

private:
    class Private;
    Private* d;
};

}

#endif // PROPERTIES_H
