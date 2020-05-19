#include "qamqptable.h"
#include "qamqpframe_p.h"
#include "qamqpauthenticator.h"

QAmqpAMQPlainAuthenticator::QAmqpAMQPlainAuthenticator(const QString &l, const QString &p)
    : login_(l),
      password_(p)
{
}

QAmqpAMQPlainAuthenticator::~QAmqpAMQPlainAuthenticator()
{
}

QString QAmqpAMQPlainAuthenticator::login() const
{
    return login_;
}

QString QAmqpAMQPlainAuthenticator::password() const
{
    return password_;
}

QString QAmqpAMQPlainAuthenticator::type() const
{
    return "AMQPLAIN";
}

void QAmqpAMQPlainAuthenticator::setLogin(const QString &l)
{
    login_ = l;
}

void QAmqpAMQPlainAuthenticator::setPassword(const QString &p)
{
    password_ = p;
}

void QAmqpAMQPlainAuthenticator::write(QDataStream &out)
{
    QAmqpFrame::writeAmqpField(out, QAmqpMetaType::ShortString, type());
    QAmqpTable response;
    response["LOGIN"] = login_;
    response["PASSWORD"] = password_;
    out << response;
}


QAmqpPlainAuthenticator::QAmqpPlainAuthenticator(const QString &l, const QString &p)
   : login_(l),
   password_(p)
{
}

QAmqpPlainAuthenticator::~QAmqpPlainAuthenticator()
{
}

QString QAmqpPlainAuthenticator::login() const
{
   return login_;
}

QString QAmqpPlainAuthenticator::password() const
{
   return password_;
}

QString QAmqpPlainAuthenticator::type() const
{
   return "PLAIN";
}

void QAmqpPlainAuthenticator::setLogin(const QString &l)
{
   login_ = l;
}

void QAmqpPlainAuthenticator::setPassword(const QString &p)
{
   password_ = p;
}

void QAmqpPlainAuthenticator::write(QDataStream &out)
{
   QAmqpFrame::writeAmqpField(out, QAmqpMetaType::ShortString, type());

   QByteArray data;
   QDataStream s(&data, QIODevice::WriteOnly);

   const quint8 nll = 0;

   s << nll;
   const auto l = login().toUtf8();
   const auto p = password().toUtf8();

   s.writeRawData(l.constData(), l.size());
   s << nll;
   s.writeRawData(p.constData(), p.size());

   out << data;
}