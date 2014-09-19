#ifndef ORGFILE_H
#define ORGFILE_H

#include <QCoreApplication>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT OrgFile : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(OrgFile)
public:
    OrgFile();
    ~OrgFile();

    void setFileName(const QString& fileName);
    QString fileName() const;

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;
private:
    class Private;
    Private* d;
};

}

#endif // ORGFILE_H
