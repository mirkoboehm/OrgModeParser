#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QCoreApplication>
#include <QVector>

#include "orgmodeparser_export.h"
#include <OrgElement.h>

namespace OrgMode {

/** @brief A helper to handle key-value properties.
 *
 * FIXME Where to keep?
 */
struct Property {
    QString key;
    QString value;
};

/** @brief Attributes handles file attributes for an OrgElement.
 *
 * File attributes are notated in "#+ATTRIBUTE:" syntax. They are used to specify the author or title of a
 * document.
 * Properties are a special type of attributes that can be inherited and manipulated while the element tree
 * is traversed.
 */
class ORGMODEPARSER_EXPORT Attributes
{
    Q_DECLARE_TR_FUNCTIONS(Attributes)
public:
    typedef QVector<Property> Vector;

    explicit Attributes(const OrgElement::Pointer& element);
    ~Attributes();


    QString fileAttribute(const QString& key) const;
    Vector fileAttributes(const QString& key) const;
    Vector fileAttributes() const;

    const QStringList drawerNames() const;

    static QString attribute(const Vector& attributes, const QString& key);

private:
    class Private;
    Private* d;
};

}

#endif // ATTRIBUTES_H
