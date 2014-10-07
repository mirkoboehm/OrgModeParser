#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QCoreApplication>

#include "orgmodeparser_export.h"
#include <OrgElement.h>

namespace OrgMode {

/** @brief The Properties class calculates the values of file attributes and properties for an element.
 *
 * It handles attributes and properties because they are syntactially the same, based on file attributes
 * and drawers. Properties are file attributes and drawers with special names.
 */
class ORGMODEPARSER_EXPORT Properties
{
    Q_DECLARE_TR_FUNCTIONS(Properties)
public:
    typedef QMap<QString, QString> PropertiesMap;

    explicit Properties(const OrgElement::Pointer& element);
    ~Properties();

    QString property(const QString&) const;
    PropertiesMap properties() const;

    QString fileAttribute(const QString& key) const;
    PropertiesMap fileAttributes() const;

private:
    class Private;
    Private* d;
};

}

#endif // PROPERTIES_H
