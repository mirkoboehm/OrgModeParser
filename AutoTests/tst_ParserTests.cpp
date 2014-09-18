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
        if (!orgFile.open(QIODevice::ReadOnly)) {
            throw RuntimeException(tr("Unable to open device for reading: %1.").arg(orgFile.errorString()));
        }
        QTextStream stream(&orgFile);
        Parser parser;
        auto element = parser.parse(&stream);
        qDebug() << endl << qPrintable(element->describe());
        QCOMPARE(element->children().count(), 4);
    } catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
}

QTEST_MAIN(ParserTests)

#include "tst_ParserTests.moc"
