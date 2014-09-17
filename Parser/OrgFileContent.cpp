#include <QTextStream>

#include "OrgFileContent.h"

namespace OrgMode {

OrgFileContent::OrgFileContent(QTextStream *data)
    : data_(data)
{
}

QString OrgFileContent::getLine()
{
    if (!lines_.isEmpty()) {
        return lines_.takeFirst();
    } else if (data_) {
        return data_->readLine();
    } else {
        return QString();
    }
}

bool OrgFileContent::isValid() const
{
    return data_ != 0;
}

void OrgFileContent::ungetLine(const QString &line)
{
    if (!line.isNull()) {
        lines_.append(line);
    }
}

bool OrgFileContent::atEnd() const
{
    return lines_.isEmpty() && data_->atEnd();
}

}
