#ifndef WRITER_H
#define WRITER_H

#include "orgmodeparser_export.h"

#include <OrgElement.h>

class QTextStream;

namespace OrgMode {

class ORGMODEPARSER_EXPORT Writer
{
public:
    Writer();

    void writeTo(QTextStream* stream, OrgElement::Pointer element);
};

}

#endif // WRITER_H
