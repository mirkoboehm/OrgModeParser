#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <OrgFileContent.h>
#include <Headline.h>
#include <Parser.h>
#include <Writer.h>
#include <OrgFile.h>
#include <Clock.h>
#include <Tags.h>
#include <OrgLine.h>
#include <FileAttributeLine.h>
#include <Properties.h>
#include <Exception.h>
#include <Drawer.h>
#include <DrawerEntry.h>

using namespace OrgMode;

typedef void (*VerificationMethod)(const QByteArray& input, const QByteArray& output, OrgElement::Pointer element);
Q_DECLARE_METATYPE(VerificationMethod)

class ParserTests : public QObject
{
    Q_OBJECT

public:
    ParserTests();

private Q_SLOTS:
    void testOrgFileContent();
    void testParserAndIdentity_data();
    void testParserAndIdentity();
};

QString FL1(const char* text) {
    return QString::fromLatin1(text);
}

ParserTests::ParserTests()
{
}

void ParserTests::testOrgFileContent()
{
    OrgFileContent content;
    QVERIFY(content.atEnd());
    const QString line1(FL1("1"));
    const QString line2(FL1("2"));
    content.ungetLine(line1);
    content.ungetLine(line2);
    QVERIFY(!content.atEnd());
    //Now LIFO-style, line2 is expected first, line1 second:
    QCOMPARE(content.getLine(), line2);
    QCOMPARE(content.getLine(), line1);
    QVERIFY(content.atEnd());
}

void ParserTests::testParserAndIdentity_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<VerificationMethod>("method");

    //Verification of the properties of SimpleTree.org:
    VerificationMethod testSimpleTree = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        QCOMPARE(element->children().count(), 4);
        QVERIFY(findElement<OrgMode::Headline>(element, QLatin1String("Headline 1")));
        QVERIFY(findElement<OrgMode::Headline>(element, QLatin1String("Headline 1.1")));
        QVERIFY(findElement<OrgMode::Headline>(element, QLatin1String("Headline 1.2")));
        QVERIFY(findElement<OrgMode::Headline>(element, QLatin1String("Headline 2")));
        QVERIFY(!findElement<OrgMode::Headline>(element, QLatin1String("Headline 3")));
        //This finds the opening line by regular expression:
        QVERIFY(findElement<OrgMode::OrgLine>(element, QLatin1String("OrgMode file that the parser should parse")));
        //This line does not exist:
        QVERIFY(!findElement<OrgMode::OrgLine>(element, QLatin1String("There is no line like this")));
    };
    QTest::newRow("SimpleTree") << FL1("://TestData/Parser/SimpleTree.org") << testSimpleTree;

    //Verify that CLOCK: lines are detected, parsed, and the numbers calculated and aggregated up the tree:
    VerificationMethod testClockEntries = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 1.1 contians one clock entry:
        QCOMPARE(Clock(findElement<OrgMode::Headline>(element, QLatin1String("headline_1_1"))).duration(), 10 * 60);
        //Headline 1.2 contains two clock entries that need to be accumulated:
        QCOMPARE(Clock(findElement<OrgMode::Headline>(element, QLatin1String("headline_1_2"))).duration(), 20 * 60);
        //Headline 1 is the parent of 1.1 and 1.2 and should have their times added up:
        QCOMPARE(Clock(findElement<OrgMode::Headline>(element, QLatin1String("headline_1"))).duration(), 30 * 60);
    };
    QTest::newRow("ClockEntries") << FL1("://TestData/Parser/ClockEntries.org") << testClockEntries;

    //Verify that tags are parsed and can be retrieved:
    VerificationMethod testTagParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 1 only has TAG1:
        static QRegularExpression headline1Regex(QLatin1String("headline_1"));
        Headline::Pointer headline_1 = findElement<OrgMode::Headline>(element, headline1Regex);
        QVERIFY(headline_1);
        Tags tags_1(headline_1);
        QVERIFY(tags_1.hasTag(QLatin1String("TAG1")));
        QVERIFY(!tags_1.hasTag(QLatin1String("NONSENSE")));
        //Headline 1.1 is tagged TAG2 and inherits TAG1 from headline 1:
        static QRegularExpression headline1_1Regex(QLatin1String("headline_1_1"));
        Headline::Pointer headline_1_1 = findElement<OrgMode::Headline>(element, headline1_1Regex);
        QVERIFY(headline_1_1);
        Tags tags_1_1(headline_1_1);
        QVERIFY(tags_1_1.hasTag(QLatin1String("TAG1"))); // inherited
        QVERIFY(tags_1_1.hasTag(QLatin1String("TAG2"))); // directly
        QVERIFY(!tags_1_1.hasTag(QLatin1String("NONSENSE")));
        //Headline 1.2 has two tags (this tests parsing of multiple tags):
        static QRegularExpression headline1_2Regex(QLatin1String("headline_1_2"));
        Headline::Pointer headline_1_2 = findElement<OrgMode::Headline>(element, headline1_2Regex);
        QVERIFY(headline_1_2);
        Tags tags_1_2(headline_1_2);
        QVERIFY(tags_1_2.hasTag(QLatin1String("TAG1"))); // inherited
        QVERIFY(tags_1_2.hasTag(QLatin1String("TEST"))); // directly
        QVERIFY(tags_1_2.hasTag(QLatin1String("VERIFY"))); // directly
        QVERIFY(!tags_1_2.hasTag(QLatin1String("NONSENSE")));
    };
    QTest::newRow("Tags") << FL1("://TestData/Parser/Tags.org") << testTagParsing;

    //Verify parsing of file attributes (#+ATTRIBUTE: value):
    VerificationMethod testAttributeParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Test for an existing, non-empty attribute:
        auto const attributeLine = findElement<OrgMode::FileAttributeLine>(element, FL1("DRAWERS"));
        QVERIFY(attributeLine);
        QCOMPARE(attributeLine->value(), FL1("MyDrawers TestDrawer"));
        //An existing but empty file attribute:
        auto const emptyAttribute = findElement<OrgMode::FileAttributeLine>(element, FL1("EMPTY_ATTRIBUTE"));
        QVERIFY(emptyAttribute);
        QVERIFY(emptyAttribute->value().isEmpty());
        //A non-existant file attribute:
        auto const nonExistentAttribute = findElement<OrgMode::FileAttributeLine>(element, FL1("I DO NOT EXIST"));
        QVERIFY(!nonExistentAttribute);
    };
    QTest::newRow("AttributeParsing") << FL1("://TestData/Parser/DrawersAndProperties.org") << testAttributeParsing;

    //Verify calculation of attributes at file scope by the Properties class:
    VerificationMethod testFileAttributes = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 1 inherits the attributes from the attributes of the file it is in:
        auto const headline_1 = findElement<OrgMode::Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        Properties properties(headline_1);
        //A file level attribute:
        QVERIFY(properties.fileAttribute(FL1("DRAWERS")).contains(FL1("MyDrawers")));
        //A file level attribute, but empty:
        QCOMPARE(properties.fileAttribute(FL1("EMPTY_ATTRIBUTE")), FL1(""));
        //A non-existant attribute:
        QCOMPARE(properties.fileAttribute(FL1("I DO NOT EXIST")), QString());
    };
    QTest::newRow("FileAttributes") << FL1("://TestData/Parser/DrawersAndProperties.org") << testFileAttributes;

    //Test two-pass parsing that provides the file properties first that will influence element parsing later:
    VerificationMethod testTwoPassParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Drawers are only identified if the first pass yielded a value for the #+DRAWERS: property
        auto const headline_1 = findElement<OrgMode::Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        auto const myDrawer = findElement<OrgMode::Drawer>(headline_1, FL1("MyDrawers"));
        QVERIFY(myDrawer);
        //Verify that content in drawer syntax is not considered a drawer if the name is not in #+DRAWERS:
        auto const headline_2 = findElement<OrgMode::Headline>(element, FL1("headline_2"));
        QVERIFY(headline_2);
        auto const notADrawer = findElement<OrgMode::Drawer>(headline_2, FL1("NotADrawer"));
        QVERIFY(!notADrawer);
    };
    QTest::newRow("TwoPassParsing") << FL1("://TestData/Parser/DrawersAndProperties.org") << testTwoPassParsing;

    //Test regular drawer parsing
    VerificationMethod testDrawerParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        auto const headline_1 = findElement<OrgMode::Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        auto const myDrawer = findElement<OrgMode::Drawer>(headline_1, FL1("MyDrawers"));
        QVERIFY(myDrawer);
        //Verify value of the "Monday" entry:
        auto const mondayEntry = findElement<OrgMode::DrawerEntry>(headline_1, FL1("Monday"));
        QVERIFY(mondayEntry);
        QCOMPARE(mondayEntry->value(), FL1("yellow"));
        //Verify value of the "Sunday" entry, it is empty:
        auto const sundayEntry = findElement<OrgMode::DrawerEntry>(headline_1, FL1("Sunday"));
        QVERIFY(sundayEntry);
        QCOMPARE(sundayEntry->value(), FL1(""));
        //Check for a non-existant entry:
        auto const thursdayEntry = findElement<OrgMode::DrawerEntry>(headline_1, FL1("Thursday"));
        QVERIFY(thursdayEntry == 0);
    };
    QTest::newRow("DrawerParsing") << FL1("://TestData/Parser/DrawersAndProperties.org") << testDrawerParsing;

    //Test corner cases of drawer parsing
    VerificationMethod testDrawerCornerCases = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //headline_1 has no drawer, because the drawer title line has text after the closing colon
        auto const headline_1 = findElement<OrgMode::Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        auto const headline1TestDrawer = findElement<OrgMode::Drawer>(headline_1, FL1("TestDrawer"));
        QVERIFY(!headline1TestDrawer);
        //headline_2 has a drawer. It has text after the closing :END:, but OrgMode accepts that
        auto const headline_2 = findElement<OrgMode::Headline>(element, FL1("headline_2"));
        QVERIFY(headline_2);
        auto const headline2TestDrawer = findElement<OrgMode::Drawer>(headline_2, FL1("TestDrawer"));
        QVERIFY(headline2TestDrawer);
        auto const testEntry = findElement<OrgMode::DrawerEntry>(headline2TestDrawer, FL1("TestValue"));
        QVERIFY(testEntry);
        QCOMPARE(testEntry->value(), FL1("1"));
        //headline_3 does not contain a drawer, because a new headline starts in the middle of it:
        //qDebug() << endl << qPrintable(element->describe());
        auto const headline_3 = findElement<OrgMode::Headline>(element, FL1("headline_3"));
        QVERIFY(headline_3);
        auto const headline3TestDrawer = findElement<OrgMode::Drawer>(headline_3, FL1("TestDrawer"));
        QVERIFY(!headline3TestDrawer);

    };
    QTest::newRow("DrawerCornerCases") << FL1("://TestData/Parser/DrawersCornerCases.org") << testDrawerCornerCases;

    //Verify calculation of properties for individual elements:
    VerificationMethod testDrawerEntries = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 1 contains a drawer "MyDrawers":
        auto const headline_1 = findElement<OrgMode::Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        const Properties properties1(headline_1);
        const Properties::Map myDrawers = properties1.drawer(FL1("MyDrawers"));
        //A drawer entry:
        QCOMPARE(myDrawers.value(FL1("Monday")), FL1("yellow"));
        //An empty drawer entry:
        QVERIFY(myDrawers.value(FL1("Sunday")).contains(FL1("")));
        //A no-existant drawer entry:
        QVERIFY(myDrawers.value(FL1("Thursday")).isNull());
    };
    QTest::newRow("DrawerEntries") << FL1("://TestData/Parser/DrawersAndProperties.org") << testDrawerEntries;

    //Verify drawers are only detected as children of an element, not in the elements children:
    VerificationMethod testDrawerInHierarchy = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 2 does not have a drawer "MyDrawers", but it's child headline_2_1 does:
        auto const headline_2 = findElement<OrgMode::Headline>(element, FL1("headline_2"));
        const Properties properties_2(headline_2);
        try {
            properties_2.drawer(FL1("MyDrawers"));
        } catch(const RuntimeException&) {
            // pass
        }
        auto const headline_2_1 = findElement<OrgMode::Headline>(element, FL1("headline_2_1"));
        const Properties properties_2_1(headline_2_1);
        auto const drawer_2_1 = properties_2_1.drawer(FL1("MyDrawers"));
        QCOMPARE(drawer_2_1.value(FL1("Monday")), FL1("yellow"));
    };
    QTest::newRow("DrawerInHierarchy") << FL1("://TestData/Parser/DrawersAndProperties.org") << testDrawerInHierarchy;

    //FIXME these aren't properties, but attributes.
    //Properties are of the syntax #+PROPERTY: key <value>.
    //See http://orgmode.org/manual/Property-syntax.html.
    //FIXME Implement and test examples from http://orgmode.org/manual/Property-syntax.html.
    //(See OrgModePropertiesExample.org resource.)

    //Verify detection of file-scope properties ("#+PROPERTY: var 123"):
    VerificationMethod testFileScopeProperties = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //QFAIL("NI");
    };
    QTest::newRow("FileScopeProperties") << FL1("://TestData/Parser/DrawersAndProperties.org") << testFileScopeProperties;

    //Verify calculation of properties for individual elements:
    VerificationMethod testElementProperties = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //QFAIL("NI");
    };
    QTest::newRow("ElementProperties") << FL1("://TestData/Parser/DrawersAndProperties.org") << testElementProperties;

    //FIXME org-use-property-inheritance as a property parser status?
    //Verify inheritance of properties:
    VerificationMethod testPropertyInheritance = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //QFAIL("NI");
    };
    QTest::newRow("PropertyInheritance") << FL1("://TestData/Parser/DrawersAndProperties.org") << testPropertyInheritance;
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
    if (input != output) {
        qDebug() << endl
                 << "---------- STRUCTURE --------" << endl
                 << endl << qPrintable(element->describe()) << endl
                 << "------------ INPUT  ---------" << endl
                 << input
                 << "------------ OUTPUT ---------" << endl
                 << output;
    }
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
