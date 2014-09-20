#include <QTextStream>

#include "Writer.h"

namespace OrgMode {

Writer::Writer()
{
}

void Writer::writeTo(QTextStream *stream, OrgElement::Pointer element)
{
    const QString line = element->line();
    if (!line.isNull()) {
        *stream << line << endl;
    }
    auto children = element->children();
    for(auto child : children) {
        writeTo(stream, child);
    }
}

}
