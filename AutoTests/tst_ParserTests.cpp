/** OrgModeParser - a parser for Emacs Org Mode files, written in C++.
    Copyright (C) 2015 Mirko Boehm

    This file is part of OrgModeParser.
    OrgModeParser is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, version 3 of the
    License.

    OrgModeParser is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the GNU General Public License for more details. You should
    have received a copy of the GNU General Public License along with
    OrgModeParser. If not, see <http://www.gnu.org/licenses/>.
*/
#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <OrgFileContent.h>
#include <Headline.h>
#include <Parser.h>
#include <Writer.h>
#include <OrgFile.h>
#include <Clock.h>
#include <CompletedClockLine.h>
#include <ClockLine.h>
#include <Tags.h>
#include <OrgLine.h>
#include <FileAttributeLine.h>
#include <Properties.h>
#include <Exception.h>
#include <Drawer.h>
#include <DrawerEntry.h>
#include <PropertyDrawer.h>
#include <PropertyDrawerEntry.h>
#include <FindElements.h>

#include "TestHelpers.h"

using namespace OrgMode;
using namespace std;

typedef void (*VerificationMethod)(const QByteArray& input, const QByteArray& output, OrgElement::Pointer element);
Q_DECLARE_METATYPE(VerificationMethod)

class ParserTests : public QObject
{
    Q_OBJECT

public:
    ParserTests();

private Q_SLOTS:
    void testOrgFileContent();
    void testParseAttributesAsProperty_data();
    void testParseAttributesAsProperty();
    void testPropertyOperations();
    void testParserAndIdentity_data();
    void testParserAndIdentity();
};

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

void ParserTests::testParseAttributesAsProperty_data()
{
    QTest::addColumn<Property>("input");
    QTest::addColumn<Property>("result");

    QTest::newRow("NDisks_ALL")
            << Property(FL1("PROPERTY"), FL1("NDisks_ALL 1 2 3 4"))
            << Property(FL1("NDisks_ALL"), FL1("1 2 3 4"));
    QTest::newRow("var")
            << Property(FL1("PROPERTY"), FL1("var  foo=1"))
            << Property(FL1("var"), FL1("foo=1"));
    QTest::newRow("var+")
            << Property(FL1("PROPERTY"), FL1("var+ bar=2"))
            << Property(FL1("var"), FL1("bar=2"), Property::Property_Add);
}

void ParserTests::testParseAttributesAsProperty()
{
    QFETCH(Property, input);
    QFETCH(Property, result);

    const Property output = Properties::parseAttributeAsProperty(input);
    QCOMPARE(output, result);
}

void ParserTests::testPropertyOperations()
{
    const QString key(FL1("TEST"));
    const QString value1(FL1("A"));
    const QString value2(FL1("B"));
    const QString added(FL1("A B"));

    //The default is to "define" a property
    Property prop1(key, value1);
    //A second property that adds a value:
    Property prop2;
    prop2 = Property(key, value2, Property::Property_Add); //Use the assignment operator

    Property result(key, value2);
    QCOMPARE(result.key(), key);
    QCOMPARE(result.value(), value2);
    //By defining a property, it's value is replaced:
    result.apply(prop1);
    QCOMPARE(result.key(), key);
    QCOMPARE(result.value(), value1);
    //prop2 adds a value to the existing value:
    result.apply(prop2);
    QCOMPARE(result.key(), key);
    QCOMPARE(result.value(), added);
}

void ParserTests::testParserAndIdentity_data()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<VerificationMethod>("method");

    //Verification of the properties of SimpleTree.org:
    VerificationMethod testSimpleTree = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        QCOMPARE(element->children().count(), 4);
        QVERIFY(findElement<Headline>(element, QLatin1String("Headline 1")));
        QVERIFY(findElement<Headline>(element, QLatin1String("Headline 1.1")));
        QVERIFY(findElement<Headline>(element, QLatin1String("Headline 1.2")));
        QVERIFY(findElement<Headline>(element, QLatin1String("Headline 2")));
        QVERIFY(!findElement<Headline>(element, QLatin1String("Headline 3")));
        //This finds the opening line by regular expression:
        QVERIFY(findElement<OrgLine>(element, QLatin1String("OrgMode file that the parser should parse")));
        //This line does not exist:
        QVERIFY(!findElement<OrgLine>(element, QLatin1String("There is no line like this")));
    };
    QTest::newRow("SimpleTree") << FL1("://TestData/Parser/SimpleTree.org") << testSimpleTree;

    //Verify that CLOCK: lines are detected, parsed, and the numbers calculated and aggregated up the tree:
    VerificationMethod testClockEntries = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 1.1 contains one clock entry:
        QCOMPARE(Clock(findElement<Headline>(element, QLatin1String("headline_1_1"))).duration(), 10 * 60);
        //Headline 1.2 contains two clock entries that need to be accumulated:
        QCOMPARE(Clock(findElement<Headline>(element, QLatin1String("headline_1_2"))).duration(), 20 * 60);
        //Headline 1 is the parent of 1.1 and 1.2 and should have their times added up:
        QCOMPARE(Clock(findElement<Headline>(element, QLatin1String("headline_1"))).duration(), 30 * 60);
        //Verify parsing of the incomplete clock line that starts at 14:30 (child of headline_1_2)
        auto const headline_1_2 = findElement<Headline>(element, QLatin1String("headline_1_2"));
        QVERIFY(headline_1_2);
        auto complete = findElements<CompletedClockLine>(headline_1_2);
        QCOMPARE(complete.size(), 2); // complete clock lines are also incomplete clock lines
        auto all = findElements<ClockLine>(headline_1_2);
        QCOMPARE(all.size(), 3); // complete clock lines are also incomplete clock lines
        //Store the difference between the two sets of elements in a vector:
        sort(all.begin(), all.end());
        sort(complete.begin(), complete.end());
        vector<OrgElement::Pointer> difference;
        set_difference(all.begin(), all.end(), complete.begin(), complete.end(), back_inserter(difference));
        //Verify:
        QVERIFY(difference.size()==1);
        QVERIFY(!difference.at(0).dynamicCast<CompletedClockLine>());
        auto const incomplete = difference.at(0).dynamicCast<ClockLine>();
        QVERIFY(incomplete);
        QCOMPARE(incomplete->startTime(), QDateTime(QDate(2014, 9, 20), QTime(14, 30)));
    };
    QTest::newRow("ClockEntries") << FL1("://TestData/Parser/ClockEntries.org") << testClockEntries;

    //Verify that tags are parsed and can be retrieved:
    VerificationMethod testTagParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 1 only has TAG1:
        static QRegularExpression headline1Regex(QLatin1String("headline_1"));
        Headline::Pointer headline_1 = findElement<Headline>(element, headline1Regex);
        QVERIFY(headline_1);
        Tags tags_1(headline_1);
        QVERIFY(tags_1.hasTag(QLatin1String("TAG1")));
        QVERIFY(!tags_1.hasTag(QLatin1String("NONSENSE")));
        //Headline 1.1 is tagged TAG2 and inherits TAG1 from headline 1:
        static QRegularExpression headline1_1Regex(QLatin1String("headline_1_1"));
        Headline::Pointer headline_1_1 = findElement<Headline>(element, headline1_1Regex);
        QVERIFY(headline_1_1);
        Tags tags_1_1(headline_1_1);
        QVERIFY(tags_1_1.hasTag(QLatin1String("TAG1"))); // inherited
        QVERIFY(tags_1_1.hasTag(QLatin1String("TAG2"))); // directly
        QVERIFY(!tags_1_1.hasTag(QLatin1String("NONSENSE")));
        //Headline 1.2 has two tags (this tests parsing of multiple tags):
        static QRegularExpression headline1_2Regex(QLatin1String("headline_1_2"));
        Headline::Pointer headline_1_2 = findElement<Headline>(element, headline1_2Regex);
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
        auto const attributeLine = findElement<FileAttributeLine>(element, FL1("DRAWERS"));
        QVERIFY(attributeLine);
        QCOMPARE(attributeLine->value(), FL1("MyDrawers TestDrawer"));
        //An existing but empty file attribute:
        auto const emptyAttribute = findElement<FileAttributeLine>(element, FL1("EMPTY_ATTRIBUTE"));
        QVERIFY(emptyAttribute);
        QVERIFY(emptyAttribute->value().isEmpty());
        //A non-existant file attribute:
        auto const nonExistentAttribute = findElement<FileAttributeLine>(element, FL1("I DO NOT EXIST"));
        QVERIFY(!nonExistentAttribute);
    };
    QTest::newRow("AttributeParsing") << FL1("://TestData/Parser/DrawersAndProperties.org") << testAttributeParsing;

    //Verify parsing of drawer names in Attributes:
    VerificationMethod testDrawerNameParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        const Attributes attributes(element);
        const QStringList drawers = attributes.drawerNames();
        QCOMPARE(drawers.count(), 3);
        QVERIFY(drawers.contains(FL1("MyDrawers")));
        QVERIFY(drawers.contains(FL1("TestDrawer")));
        QVERIFY(drawers.contains(FL1("PROPERTIES")));
    };
    QTest::newRow("DrawerNameParsing") << FL1("://TestData/Parser/DrawersAndProperties.org") << testDrawerNameParsing;

    //Verify calculation of attributes at file scope by the Properties class:
    VerificationMethod testFileAttributes = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 1 inherits the attributes from the attributes of the file it is in:
        auto const headline_1 = findElement<Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        Attributes attributes(headline_1);
        //A file level attribute:
        QCOMPARE(attributes.fileAttribute(FL1("DRAWERS")), FL1("MyDrawers TestDrawer"));
        //A file level attribute, but empty:
        QCOMPARE(attributes.fileAttribute(FL1("EMPTY_ATTRIBUTE")), FL1(""));
        //A non-existant attribute:
        try {
            attributes.fileAttribute(FL1("I DO NOT EXIST"));
            QFAIL("Querying a non-existant attribute should throw an exception.");
        } catch (const RuntimeException&) {
            //all good
        }
    };
    QTest::newRow("FileAttributes") << FL1("://TestData/Parser/DrawersAndProperties.org") << testFileAttributes;

    //Test two-pass parsing that provides the file properties first that will influence element parsing later:
    VerificationMethod testTwoPassParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Drawers are only identified if the first pass yielded a value for the #+DRAWERS: property
        auto const headline_1 = findElement<Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        auto const myDrawer = findElement<Drawer>(headline_1, FL1("MyDrawers"));
        QVERIFY(myDrawer);
        //Verify that content in drawer syntax is not considered a drawer if the name is not in #+DRAWERS:
        auto const headline_2 = findElement<Headline>(element, FL1("headline_2"));
        QVERIFY(headline_2);
        auto const notADrawer = findElement<Drawer>(headline_2, FL1("NotADrawer"));
        QVERIFY(!notADrawer);
    };
    QTest::newRow("TwoPassParsing") << FL1("://TestData/Parser/DrawersAndProperties.org") << testTwoPassParsing;

    //Test regular drawer parsing
    VerificationMethod testDrawerParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        auto const headline_1 = findElement<Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        auto const myDrawer = findElement<Drawer>(headline_1, FL1("MyDrawers"));
        QVERIFY(myDrawer);
        //Verify value of the "Monday" entry:
        auto const mondayEntry = findElement<DrawerEntry>(headline_1, FL1("Monday"));
        QVERIFY(mondayEntry);
        QCOMPARE(mondayEntry->value(), FL1("yellow"));
        //Verify value of the "Saturday"entry, it contains a colon:
        auto const saturdayEntry = findElement<DrawerEntry>(headline_1, FL1("Saturday"));
        QVERIFY(saturdayEntry);
        QCOMPARE(saturdayEntry->value(), FL1("party: going commando"));
        QCOMPARE(saturdayEntry->key(), FL1("Saturday"));
        //Verify value of the "Sunday" entry, it is empty:
        auto const sundayEntry = findElement<DrawerEntry>(headline_1, FL1("Sunday"));
        QVERIFY(sundayEntry);
        QCOMPARE(sundayEntry->value(), FL1(""));
        //Check for a non-existant entry:
        auto const thursdayEntry = findElement<DrawerEntry>(headline_1, FL1("Thursday"));
        QVERIFY(thursdayEntry == nullptr);
    };
    QTest::newRow("DrawerParsing") << FL1("://TestData/Parser/DrawersAndProperties.org") << testDrawerParsing;

    //Test corner cases of drawer parsing
    VerificationMethod testDrawerCornerCases = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //headline_1 has no drawer, because the drawer title line has text after the closing colon
        auto const headline_1 = findElement<Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        auto const headline1TestDrawer = findElement<Drawer>(headline_1, FL1("TestDrawer"));
        QVERIFY(!headline1TestDrawer);
        //headline_2 has a drawer. It has text after the closing :END:, but OrgMode accepts that
        auto const headline_2 = findElement<Headline>(element, FL1("headline_2"));
        QVERIFY(headline_2);
        auto const headline2TestDrawer = findElement<Drawer>(headline_2, FL1("TestDrawer"));
        QVERIFY(headline2TestDrawer);
        auto const testEntry = findElement<DrawerEntry>(headline2TestDrawer, FL1("TestValue"));
        QVERIFY(testEntry);
        QCOMPARE(testEntry->value(), FL1("1"));
        //headline_3 does not contain a drawer, because a new headline starts in the middle of it:
        auto const headline_3 = findElement<Headline>(element, FL1("headline_3"));
        QVERIFY(headline_3);
        auto const headline3TestDrawer = findElement<Drawer>(headline_3, FL1("TestDrawer"));
        QVERIFY(!headline3TestDrawer);

    };
    QTest::newRow("DrawerCornerCases") << FL1("://TestData/Parser/DrawersCornerCases.org") << testDrawerCornerCases;

    VerificationMethod testFindElements = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        {   //There is one headline that is a direct child of element, headline_1:
            auto const headlines = findElements<Headline>(element, 1);
            QCOMPARE(headlines.size(), 1);
            const Headline::Pointer headline_1 = headlines.first();
            QCOMPARE(headline_1->caption(), FL1("headline_1"));
        }
        {   //At maxdepth 2, there are 3 headlines:
            auto const headlines = findElements<Headline>(element, 2);
            QCOMPARE(headlines.size(), 3);
            const Headline::Pointer headline_1_2 = headlines.at(2);
            QCOMPARE(headline_1_2->caption(), FL1("headline_1_2"));
        }
        {   //At maxdepth 0, there are no headlines:
            auto const headlines = findElements<Headline>(element, 0);
            QVERIFY(headlines.isEmpty());
        }
        {   //At maxdepth 0, there one OrgFile:
            auto const orgFiles = findElements<OrgFile>(element, 0);
            QCOMPARE(orgFiles.size(), 1);
            const OrgFile::Pointer orgFile = orgFiles.first();
            QCOMPARE(orgFile->fileName(), FL1("://TestData/Parser/ClockEntries.org"));
        }
    };
    QTest::newRow("FindElements") << FL1("://TestData/Parser/ClockEntries.org") << testFindElements;

    VerificationMethod testFindElementsFiltered = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //There is one headline that is a direct child of element, headline_1:
        auto const nonEmptyClockLines = [](const CompletedClockLine::Pointer& clock) { return clock->duration() > 0; };
        auto const clockLines = findElements<CompletedClockLine>(element, nonEmptyClockLines);
        QVERIFY(clockLines.size() == 3);
        const CompletedClockLine::Pointer clockLine_1_1 = clockLines.first();
        QCOMPARE(clockLine_1_1->duration(), 600);
    };
    QTest::newRow("FindElementsFiltered") << FL1("://TestData/Parser/ClockEntries.org") << testFindElementsFiltered;

    //Verify calculation of properties for individual elements:
    VerificationMethod testDrawerEntries = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 1 contains a drawer "MyDrawers":
        auto const headline_1 = findElement<Headline>(element, FL1("headline_1"));
        QVERIFY(headline_1);
        const Properties properties1(headline_1);
        const Properties::Vector myDrawers = properties1.drawer(FL1("MyDrawers"));
        //A drawer entry:
        QCOMPARE(Attributes::attribute(myDrawers, FL1("Monday")), FL1("yellow"));
        //An empty drawer entry:
        QCOMPARE(Attributes::attribute(myDrawers, FL1("Sunday")), FL1(""));
        //A no-existant drawer entry:
        QVERIFY(Attributes::attribute(myDrawers, FL1("Thursday")).isNull());
    };
    QTest::newRow("DrawerEntries") << FL1("://TestData/Parser/DrawersAndProperties.org") << testDrawerEntries;

    //Verify drawers are only detected as children of an element, not in the elements children:
    VerificationMethod testDrawerInHierarchy = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //Headline 2 does not have a drawer "MyDrawers", but it's child headline_2_1 does:
        auto const headline_2 = findElement<Headline>(element, FL1("headline_2"));
        const Properties properties_2(headline_2);
        try {
            properties_2.drawer(FL1("MyDrawers"));
            QFAIL("Retrieving a non-existant drawer should throw an exception!");
        } catch(const RuntimeException&) {
            //qDebug() << qPrintable(ex.message());
        }
        auto const headline_2_1 = findElement<Headline>(element, FL1("headline_2_1"));
        const Properties properties_2_1(headline_2_1);
        auto const drawer_2_1 = properties_2_1.drawer(FL1("MyDrawers"));
        QCOMPARE(Attributes::attribute(drawer_2_1, FL1("Monday")), FL1("yellow"));
    };
    QTest::newRow("DrawerInHierarchy") << FL1("://TestData/Parser/DrawersAndProperties.org") << testDrawerInHierarchy;

    //Verify property drawers are detected:
    VerificationMethod testPropertyDrawerParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        auto const headline = findElement<Headline>(element, FL1("CD collection"));
        QVERIFY(headline);
        auto const drawers = findElements<PropertyDrawer>(headline, 1);
        QCOMPARE(drawers.count(), 1);
        auto const allPropertyDrawers = findElements<PropertyDrawer>(headline);
        QCOMPARE(allPropertyDrawers.count(), 3);
    };
    QTest::newRow("PropertyDrawerParsing") << FL1("://TestData/Parser/OrgModePropertiesExample.org") << testPropertyDrawerParsing;

    //Verify property drawers are detected:
    VerificationMethod testPropertyDrawerEntryParsing = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //qDebug() << endl << qPrintable(element->describe());
        auto const headline = findElement<Headline>(element, FL1("CD collection"));
        QVERIFY(headline);
        auto const entries = findElements<PropertyDrawerEntry>(headline, 2);
        QCOMPARE(entries.count(), 2);
    };
    QTest::newRow("PropertyDrawerEntryParsing") << FL1("://TestData/Parser/OrgModePropertiesExample.org")
                                                << testPropertyDrawerEntryParsing;

    //Verify detection of file-scope properties ("#+PROPERTY: var 123"):
    VerificationMethod testFileScopeProperties = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        {   //Verify value of file level property NDisks_ALL:
            Properties properties(element);
            QCOMPARE(properties.property(FL1("NDisks_ALL")), FL1("1 2 3 4"));
        }
        {   //Verify value of file level property var, assembled over two lines
            Properties properties(element);
            QCOMPARE(properties.property(FL1("var")), FL1("foo=1 bar=2"));
        }
    };
    QTest::newRow("FileScopeProperties") << FL1("://TestData/Parser/OrgModePropertiesExample.org") << testFileScopeProperties;

    //Verify calculation of properties for individual elements:
    VerificationMethod testElementProperties = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        {   //Verify values of the properties of the level 3 headlines:
            auto const goldbergHeadline = findElement<Headline>(element, FL1("Goldberg Variations"));
            QVERIFY(goldbergHeadline);
            Properties properties(goldbergHeadline);
            QCOMPARE(properties.property(FL1("Artist")), FL1("Glen Gould"));
            QCOMPARE(properties.property(FL1("Composer")), FL1("J.S. Bach"));
            try { //...a non-existant property
                properties.property(FL1("I do not exist"));
                QFAIL("Retrieving a non-existant propertry should throw an exception!");
            } catch(const RuntimeException&) {
                //qDebug() << qPrintable(ex.message());
            }
        }
    };
    QTest::newRow("ElementProperties") << FL1("://TestData/Parser/OrgModePropertiesExample.org") << testElementProperties;

    //FIXME org-use-property-inheritance as a property parser status?
    //Verify inheritance of properties:
    VerificationMethod testPropertyInheritance = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        //qDebug() << endl << qPrintable(element->describe());
        {   //At the file level, the GENRES property is not defined:
            auto const orgFiles = findElements<OrgFile>(element);
            QCOMPARE(orgFiles.count(), 1);
            Properties properties(orgFiles.first());
            try { //...a non-existant property
                properties.property(FL1("GENRES"));
                QFAIL("Retrieving a non-existant propertry should throw an exception!");
            } catch(const RuntimeException&) {
                //qDebug() << qPrintable(ex.message());
            }
        }
        {   //At the "CD collection" level, the GENRES property is still not defined:
            auto const headline = findElement<Headline>(element, FL1("CD collection"));
            Properties properties(headline);
            try { //...a non-existant property
                properties.property(FL1("GENRES"));
                QFAIL("Retrieving a non-existant propertry should throw an exception!");
            } catch(const RuntimeException&) {
                //qDebug() << qPrintable(ex.message());
            }
        }
        {   //At the "Classic" level, the GENRES property is defined:
            auto const headline = findElement<Headline>(element, FL1("Classic"));
            QVERIFY(headline);
            Properties properties(headline);
            const QString value = properties.property(FL1("GENRES"));
            QCOMPARE(value, FL1("Classic"));
        }
        {   //At the "Goldberg Variations" level, the GENRES property is extended:
            auto const headline = findElement<Headline>(element, FL1("Goldberg Variations"));
            Properties properties(headline);
            const QString value = properties.property(FL1("GENRES"));
            QCOMPARE(value, FL1("Classic Baroque"));
        }
    };
    QTest::newRow("PropertyInheritance") << FL1("://TestData/Parser/OrgModePropertiesExample.org") << testPropertyInheritance;

    //Test clock lines that are kept in logbook drawers:
    VerificationMethod testLogBookDrawerClockLines = [](const QByteArray&, const QByteArray&, OrgElement::Pointer element) {
        qDebug() << Qt::endl << qPrintable(element->describe());
    };
    QTest::newRow("LogBookDrawerClockLines") << FL1("://TestData/Parser/LogbookClockEntries.org") << testLogBookDrawerClockLines;
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
        qDebug() << Qt::endl
                 << "---------- STRUCTURE --------" << Qt::endl
                 << Qt::endl << qPrintable(element->describe()) << Qt::endl
                 << "------------ INPUT  ---------" << Qt::endl
                 << input
                 << "------------ OUTPUT ---------" << Qt::endl
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
