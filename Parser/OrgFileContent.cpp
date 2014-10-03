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

void OrgFileContent::ungetLine(const QString &line)
{
    if (!line.isNull()) {
        lines_.prepend(line);
    }
}

void OrgFileContent::ungetLines(const QStringList &lines)
{
    if (!lines.isEmpty()) {
        lines_ = lines + lines_;
    }
}

bool OrgFileContent::atEnd() const
{
    return lines_.isEmpty() && (data_ == 0 || data_->atEnd());
}

}
