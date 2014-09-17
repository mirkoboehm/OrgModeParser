#ifndef HEADLINE_H
#define HEADLINE_H

#include <QCoreApplication>
#include <QSharedPointer>

#include "orgmodeparser_export.h"

class QTextStream;

namespace OrgMode {

class OrgFileContent;

/** @brief Headline represent a single headline in an OrgMode file. */
class ORGMODEPARSER_EXPORT Headline
{
    Q_DECLARE_TR_FUNCTIONS(Headline)
public:
    typedef QSharedPointer<Headline> Pointer;
    typedef QList<Pointer> List;

    Headline();
    ~Headline();
    List children() const;

    void addChild(const Pointer& child);

    int level() const;
    void setLevel(int level);

    QString caption() const;
    void setCaption(const QString& caption);

    void readFrom(OrgFileContent* content);

private:
    class Private;
    Private* d;
};

}

#endif // HEADLINE_H
