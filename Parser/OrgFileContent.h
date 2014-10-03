#ifndef ORGFILECONTENT_H
#define ORGFILECONTENT_H

#include <QStringList>

#include "orgmodeparser_export.h"

class QTextStream;

namespace OrgMode {

/** @brief OrgFileContent represents a data file and adds unget functionality for lines.
 *  It is not exported.
 */
class ORGMODEPARSER_EXPORT OrgFileContent
{
public:
    typedef QSharedPointer<OrgFileContent> Pointer;

    explicit OrgFileContent(QTextStream* data = 0);

    QString getLine();
    void ungetLine(const QString& line);
    void ungetLines(const QStringList& lines);
    bool atEnd() const;

private:
    QTextStream* data_;
    QStringList lines_;
};

}

#endif // ORGFILECONTENT_H
