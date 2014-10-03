#ifndef ATTRIBUTELINE_H
#define ATTRIBUTELINE_H

#include <QCoreApplication>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT AttributeLine : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(AttributeLine)
public:
    explicit AttributeLine(OrgElement* parent = 0);
    explicit AttributeLine(const QString& line, OrgElement* parent = 0);
    ~AttributeLine();

    void setProperty(const QString& key, const QString& value);
    QString key() const;
    QString value() const;

protected:
    bool isElementValid() const override;
    QString description() const override;

private:
    class Private;
    Private* d;
};

}

#endif // ATTRIBUTELINE_H
