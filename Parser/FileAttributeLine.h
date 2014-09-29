#ifndef FILEATTRIBUTELINE_H
#define FILEATTRIBUTELINE_H

#include <QCoreApplication>

#include <OrgLine.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT FileAttributeLine : public OrgLine
{
    Q_DECLARE_TR_FUNCTIONS(FileAttributeLine)
public:
    explicit FileAttributeLine(OrgElement* parent = 0);
    explicit FileAttributeLine(const QString& line, OrgElement* parent = 0);
    ~FileAttributeLine();

    void setProperty(const QString& key, const QString& value);
    QString key() const;
    QString value() const;

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    class Private;
    Private* d;
};

}

#endif // FILEATTRIBUTELINE_H
