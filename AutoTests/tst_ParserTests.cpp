#include <QString>
#include <QtTest>
#include <QCoreApplication>

class ParserTests : public QObject
{
    Q_OBJECT

public:
    ParserTests();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

ParserTests::ParserTests()
{
}

void ParserTests::initTestCase()
{
}

void ParserTests::cleanupTestCase()
{
}

void ParserTests::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(ParserTests)

#include "tst_ParserTests.moc"
