#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <Headline.h>
#include <Parser.h>
#include <OrgFile.h>
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
        const QString fileName(QLatin1String("://TestData/Parser/SimpleTree.org"));
        QFile orgFile(fileName);
        QVERIFY(orgFile.exists());
        if (!orgFile.open(QIODevice::ReadOnly)) {
            throw RuntimeException(tr("Unable to open device for reading: %1.").arg(orgFile.errorString()));
        }
        QTextStream stream(&orgFile);
        Parser parser;
        auto element = parser.parse(&stream);
        QCOMPARE(element->children().count(), 4);
        OrgFile* orgFileElement = dynamic_cast<OrgFile*>(element.data());
        orgFileElement->setFileName(fileName);
        qDebug() << endl << qPrintable(element->describe());
    } catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
}

QTEST_MAIN(ParserTests)

#include "tst_ParserTests.moc"
