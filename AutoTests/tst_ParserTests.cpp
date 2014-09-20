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
    void testParserAndIdentity_data();
    void testParserAndIdentity();

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

void ParserTests::testParserAndIdentity_data()
{
    QTest::addColumn<QString>("filename");
    QTest::newRow("SimpleTree") << QString::fromLatin1("://TestData/Parser/SimpleTree.org");
}

void ParserTests::testParserAndIdentity()
{
    QFETCH(QString, filename);

    OrgElement::Pointer element;
    QByteArray input;
    //Read the file into a OrgFile element:
    try {
        QFile orgFile(filename);
        QVERIFY(orgFile.exists());
        if (!orgFile.open(QIODevice::ReadOnly)) {
            throw RuntimeException(tr("Unable to open device for reading: %1.").arg(orgFile.errorString()));
        }
        input = orgFile.readAll();
        QBuffer buffer(&input);
        buffer.open(QBuffer::ReadOnly);
        QTextStream stream(&buffer);
        Parser parser;
        element = parser.parse(&stream, filename);
    } catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
    QByteArray output;
    //Write it to a QByteArray and verify input and output are identical:
    try {
        QBuffer outputBuffer(&output);
        outputBuffer.open(QBuffer::WriteOnly);
        QTextStream outputStream(&outputBuffer);
        Writer writer;
        writer.writeTo(&outputStream, element);
    }  catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
    //We now have access to the input data, the parsed element and the output data:
    QCOMPARE(input.size(), output.size());
    QCOMPARE(input, output);
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
        //qDebug() << endl << qPrintable(element->describe());

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
    // qDebug() << "fileData:" << endl << fileData << endl << "outputData:" << endl << outputData;
    QCOMPARE(fileData.size(), outputData.size());
    QCOMPARE(fileData, outputData);
}

QTEST_MAIN(ParserTests)

#include "tst_ParserTests.moc"
