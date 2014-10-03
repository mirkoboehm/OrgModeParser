#ifndef FILEATTRIBUTELINE_H
#define FILEATTRIBUTELINE_H

#include <QCoreApplication>

#include <AttributeLine.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT FileAttributeLine : public AttributeLine
{
    Q_DECLARE_TR_FUNCTIONS(FileAttributeLine)
public:
    explicit FileAttributeLine(OrgElement* parent = 0);
    explicit FileAttributeLine(const QString& line, OrgElement* parent = 0);
    ~FileAttributeLine();

protected:
    QString mnemonic() const override;

private:
    class Private;
    Private* d;
};

}

#endif // FILEATTRIBUTELINE_H
