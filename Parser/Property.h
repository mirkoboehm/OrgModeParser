#ifndef PROPERTY_H
#define PROPERTY_H

#include <QMetaType>
#include <QString>

#include "orgmodeparser_export.h"

namespace OrgMode {

/** @brief A helper to handle key-value properties.
 */
class ORGMODEPARSER_EXPORT Property {
public:
    enum Operation {
        Property_Define,
        Property_Add
    };

    Property();
    explicit Property(const QString& key, const QString& value, Operation op = Property_Define);
    Property(const Property& other);
    ~Property();
    bool operator==(const Property& other) const;

    bool isValid() const;
    void apply(const Property& token);

    QString key() const;
    void setKey(const QString& key);

    QString value() const;
    void setValue(const QString& value) const;

    Operation operation() const;
    void setOperation(Operation op);

private:
    class Private;
    Private* d;
};

}

Q_DECLARE_METATYPE(OrgMode::Property)

#endif // PROPERTY_H
