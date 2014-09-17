#ifndef HEADLINE_H
#define HEADLINE_H

#include <QCoreApplication>
#include <QSharedPointer>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

class QTextStream;

namespace OrgMode {

class OrgFileContent;

/** @brief Headline represent a single headline in an OrgMode file. */
class ORGMODEPARSER_EXPORT Headline : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(Headline)
public:

    Headline();
    ~Headline();

    QString caption() const;
    void setCaption(const QString& caption);

    void readFrom(OrgFileContent* content);

private:
    class Private;
    Private* d;
};

}

#endif // HEADLINE_H
