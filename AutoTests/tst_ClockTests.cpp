#include <QString>
#include <QtTest>
#include <QDate>
#include <QTextStream>

#include <Parser.h>
#include <Headline.h>
#include <Clock.h>
#include <Exception.h>

#include "TestHelpers.h"

using namespace OrgMode;

class ClockTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testAccumulateForDay();
    void testAccumulateForWeek();
};



void ClockTests::testAccumulateForDay()
{
    const QString filename = FL1("://TestData/Parser/WeirdClockEntries.org");
    QFile input(filename);
    QVERIFY(input.open(QIODevice::ReadOnly));
    QTextStream stream(&input);
    Parser parser;
    try {
        auto const element = parser.parse(&stream, filename);
        auto const headline_1_1 = findElement<Headline>(element, FL1("headline_1_1"));
        QVERIFY(headline_1_1);
        Clock clock(headline_1_1);
        QCOMPARE(clock.duration(), 60 * 150); //150 minutes
        const QDate mar26(2015, 3, 26);
        const QDate mar27(mar26.addDays(1));
        //QCOMPARE(clock.duration(mar26, mar27), 60 * 60); //60 minutes on March 26
    } catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
}

void ClockTests::testAccumulateForWeek()
{
}

QTEST_APPLESS_MAIN(ClockTests)

#include "tst_ClockTests.moc"
