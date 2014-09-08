#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <Headline.h>

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
    QFile orgFile(QLatin1String("://TestData/Parser/SimpleTree.org"));
    QVERIFY(orgFile.exists());
    QVERIFY(orgFile.open(QIODevice::ReadOnly));
//    Parser parser(&orgFile);
//    auto headline = parser.parse();
    QFAIL("NI");
}

QTEST_MAIN(ParserTests)

#include "tst_ParserTests.moc"
