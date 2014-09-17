#ifndef ORGLINE_H
#define ORGLINE_H

#include <OrgElement.h>

namespace OrgMode {

class OrgLine
{
public:
    OrgLine();
    ~OrgLine();

    void setText(const QString& text);
    QString text() const;

private:
    class Private;
    Private* d;
};

}

#endif // ORGLINE_H
