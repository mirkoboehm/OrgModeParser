#ifndef ORGMODE_PARSER_EXCEPTION_H
#define ORGMODE_PARSER_EXCEPTION_H

#include <QCoreApplication>

#include <stdexcept>

#include <QString>

#include "orgmodeparser_export.h"

namespace OrgMode {

class ORGMODEPARSER_EXPORT Exception : public std::runtime_error
{
public:
    explicit Exception(const QString& message);
    ~Exception() throw();
    QString message() const;

private:
    QString m_message;
};

class ORGMODEPARSER_EXPORT NotImplementedException : public Exception
{
    Q_DECLARE_TR_FUNCTIONS(NotImplementedException)
public:
    explicit NotImplementedException(const QString& message = tr("Not implemented!"));
};

class ORGMODEPARSER_EXPORT RuntimeException : public Exception
{
public :
    explicit RuntimeException(const QString& message);
};

}

#endif // ORGMODE_PARSER_EXCEPTION_H
