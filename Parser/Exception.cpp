#include "Exception.h"

namespace OrgMode {

Exception::Exception(const QString& message)
    : std::runtime_error(message.toStdString())
    , m_message(message)
{
}

Exception::~Exception() throw () {}

QString Exception::message() const
{
    return m_message;
}

NotImplementedException::NotImplementedException(const QString &message)
    : Exception(message)
{
}

RuntimeException::RuntimeException(const QString &message)
    : Exception(message)
{
}

}
