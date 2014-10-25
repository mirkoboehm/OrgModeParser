#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QCoreApplication>

#include "orgmodeparser_export.h"
#include <OrgElement.h>
#include <Attributes.h>

namespace OrgMode {

/** @brief The Properties class calculates the values of file attributes and properties for an element.
 *
 * It handles attributes and properties because they are syntactially the same, based on file attributes
 * and drawers. Properties are file attributes and drawers with special names.
 *
 * See http://orgmode.org/manual/Property-syntax.html. The OrgModePropertiesExample.org resource emulates the
 * examples from the OrgMode manual and verifies with unit tests that the results are as expected.
 */
class ORGMODEPARSER_EXPORT Properties
{
    Q_DECLARE_TR_FUNCTIONS(Properties)
public:
    typedef QVector<Property> Vector;

    explicit Properties(const OrgElement::Pointer& element);
    ~Properties();

    QString property(const QString&) const;
    Vector properties() const;

    Vector drawer(const QString& name) const;

    static QString propertyValue(const QString& key, const Vector& definitions);
private:
    class Private;
    Private* d;
};

}

#endif // PROPERTIES_H
