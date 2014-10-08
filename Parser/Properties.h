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
 *
 * See http://orgmode.org/manual/Property-syntax.html. The OrgModePropertiesExample.org resource emulates the
 * examples from the OrgMode manual and verifies with unit tests that the results are as expected.
 */
class ORGMODEPARSER_EXPORT Properties
{
    Q_DECLARE_TR_FUNCTIONS(Properties)
public:
    typedef QMap<QString, QString> Map;

    explicit Properties(const OrgElement::Pointer& element);
    ~Properties();

    QString property(const QString&) const;
    Map properties() const;

    QString fileAttribute(const QString& key) const;
    Map fileAttributes() const;

    Map drawer(const QString& name) const;
private:
    class Private;
    Private* d;
};

}

#endif // PROPERTIES_H
