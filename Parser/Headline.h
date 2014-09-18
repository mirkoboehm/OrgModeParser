#ifndef HEADLINE_H
#define HEADLINE_H

#include <QCoreApplication>
#include <QSharedPointer>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

class QTextStream;

namespace OrgMode {

/** @brief Headline represent a single headline in an OrgMode file. */
class ORGMODEPARSER_EXPORT Headline : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(Headline)
public:
    typedef QSharedPointer<Headline> Pointer;

    Headline();
    ~Headline();

    QString caption() const;
    void setCaption(const QString& caption);

protected:
    bool isElementValid() const override;
    QString mnemonic() const override;
    QString description() const override;

private:
    class Private;
    Private* d;
};

}

#endif // HEADLINE_H
