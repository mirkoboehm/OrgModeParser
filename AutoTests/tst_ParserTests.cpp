#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <Headline.h>
#include <Parser.h>
#include <Writer.h>
#include <OrgFile.h>
#include <Clock.h>
#include <Exception.h>

using namespace OrgMode;

typedef void (*VerificationMethod)(const QByteArray& input, const QByteArray& output, OrgElement::Pointer element);
Q_DECLARE_METATYPE(VerificationMethod)

class ParserTests : public QObject
{
    Q_OBJECT

public:
    ParserTests();

private Q_SLOTS:
    void testParserAndIdentity_data();
    void testParserAndIdentity();
};

ParserTests::ParserTests()
{
}

void ParserTests::testParserAndIdentity_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<VerificationMethod>("method");

    //Verification of the properties of SimpleTree.org:
    VerificationMethod testSimpleTree = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        QCOMPARE(element->children().count(), 4);
    };
    QTest::newRow("SimpleTree") << QString::fromLatin1("://TestData/Parser/SimpleTree.org") << testSimpleTree;

    //Verify that CLOCK: lines are detected, parsed, and the numbers calculated and aggregated up the tree:
    VerificationMethod testClockEntries = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        qDebug() << qPrintable(element->describe());
        Clock clock(element);
        //QCOMPARE(clock.duration(), 30 * 60); // 30 minutes
    };
    QTest::newRow("ClockEntries") << QString::fromLatin1("://TestData/Parser/ClockEntries.org") << testClockEntries;
}

void ParserTests::testParserAndIdentity()
{
    QFETCH(QString, filename);
    QFETCH(VerificationMethod, method);

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
    try {
        method(input, output, element);
    }  catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
}

QTEST_MAIN(ParserTests)

#include "tst_ParserTests.moc"
