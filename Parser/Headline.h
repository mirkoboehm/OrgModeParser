#ifndef HEADLINE_H
#define HEADLINE_H

#include <set>

#include <QCoreApplication>
#include <QSharedPointer>

#include <OrgElement.h>
#include "orgmodeparser_export.h"

namespace OrgMode {

/** @brief Headline represent a single headline in an OrgMode file. */
class ORGMODEPARSER_EXPORT Headline : public OrgElement
{
    Q_DECLARE_TR_FUNCTIONS(Headline)
public:
    typedef QSharedPointer<Headline> Pointer;
    typedef std::set<QString> Tags;

    explicit Headline(const QString& line, OrgElement* parent = 0);
    explicit Headline(OrgElement* parent = 0);
    ~Headline();

    QString caption() const;
    void setCaption(const QString& caption);

    Tags tags() const;
    void setTags(const Tags& tags);

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
