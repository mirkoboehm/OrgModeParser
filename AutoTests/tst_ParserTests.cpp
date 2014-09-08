#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <Headline.h>
#include <Parser.h>
#include <Exception.h>

using namespace OrgMode;

class ParserTests : public QObject
{
    Q_OBJECT

public:
    ParserTests();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testParseSimpleTree();
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

void ParserTests::testParseSimpleTree()
{
    try {
        QFile orgFile(QLatin1String("://TestData/Parser/SimpleTree.org"));
        QVERIFY(orgFile.exists());
        QVERIFY(orgFile.open(QIODevice::ReadOnly));
        Parser parser;
        parser.setInputDevice(&orgFile);
        auto headline = parser.parse();
        QCOMPARE(headline->children().count(), 2);
    } catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
}

QTEST_MAIN(ParserTests)

#include "tst_ParserTests.moc"
