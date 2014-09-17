#ifndef ORGFILECONTENT_H
#define ORGFILECONTENT_H

#include <QStringList>

class QTextStream;

namespace OrgMode {

/** @brief OrgFileContent represents a data file and adds unget functionality for lines.
 *  It is not exported.
 */
class OrgFileContent
{
public:
    explicit OrgFileContent(QTextStream* data = 0);
    bool isValid() const;

    QString getLine();
    void ungetLine(const QString& getLine);
    bool atEnd() const;

private:
    QTextStream* data_;
    QStringList lines_;
};

}

#endif // ORGFILECONTENT_H
