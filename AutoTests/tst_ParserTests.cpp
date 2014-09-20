#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <Headline.h>
#include <Parser.h>
#include <Writer.h>
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
    void testParseAndWriteIdentity();
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
        auto element = parser.parse(&stream, fileName);
        QCOMPARE(element->children().count(), 4);
        qDebug() << endl << qPrintable(element->describe());

    } catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
}

void ParserTests::testParseAndWriteIdentity()
{
    const QString fileName(QLatin1String("://TestData/Parser/SimpleTree.org"));
    QFile orgFile(fileName);
    QVERIFY(orgFile.exists());
    if (!orgFile.open(QIODevice::ReadOnly)) {
        throw RuntimeException(tr("Unable to open device for reading: %1.").arg(orgFile.errorString()));
    }
    QByteArray fileData = orgFile.readAll();
    QVERIFY(!fileData.isEmpty());
    QBuffer buffer(&fileData);
    buffer.open(QBuffer::ReadOnly);
    QTextStream stream(&buffer);
    Parser parser;
    auto element = parser.parse(&stream, fileName);
    QCOMPARE(element->children().count(), 4);
    QByteArray outputData;
    QBuffer outputBuffer(&outputData);
    outputBuffer.open(QBuffer::WriteOnly);
    {
        QTextStream outputStream(&outputBuffer);
        Writer writer;
        writer.writeTo(&outputStream, element);
    }
    qDebug() << "fileData:" << endl << fileData << endl << "outputData:" << endl << outputData;
    QCOMPARE(fileData.size(), outputData.size());
    QCOMPARE(fileData, outputData);
}

QTEST_MAIN(ParserTests)

#include "tst_ParserTests.moc"
