#include <QtTest/QtTest>
#include <QProcess>
#include <QSslKey>

#include "qamqptestcase.h"
#include "qamqpauthenticator.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"
#include "qamqpclient_p.h"
#include "qamqpclient.h"

class tst_QAMQPAuth : public TestCase
{
   Q_OBJECT
      private Q_SLOTS:
   void connect();
   void validPlainAuthentication();
   void validAMQPPlainAuthentication();
};

void tst_QAMQPAuth::connect()
{
   QAmqpClient client;
   client.connectToHost();
   QVERIFY(waitForSignal(&client, SIGNAL(connected())));

   QCOMPARE(client.host(), QLatin1String(AMQP_HOST));
   QCOMPARE(client.port(), quint16(AMQP_PORT));
   QCOMPARE(client.virtualHost(), QLatin1String(AMQP_VHOST));
   QCOMPARE(client.username(), QLatin1String(AMQP_LOGIN));
   QCOMPARE(client.password(), QLatin1String(AMQP_PSWD));

   client.disconnectFromHost();
   QVERIFY(waitForSignal(&client, SIGNAL(disconnected())));
}

void tst_QAMQPAuth::validPlainAuthentication()
{
   QAmqpClient client;
   client.setAuth(new QAmqpPlainAuthenticator("guest", "guest"));
   client.connectToHost();
   QVERIFY(waitForSignal(&client, SIGNAL(connected())));
}

void tst_QAMQPAuth::validAMQPPlainAuthentication()
{
   QAmqpClient client;
   client.setAuth(new QAmqpAMQPlainAuthenticator("guest", "guest"));
   client.connectToHost();
   QVERIFY(waitForSignal(&client, SIGNAL(connected())));
}

QTEST_MAIN(tst_QAMQPAuth)
#include "tst_qamqpauth.moc"
