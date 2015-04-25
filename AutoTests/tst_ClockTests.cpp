#include <limits>

#include <QString>
#include <QtTest>
#include <QDate>
#include <QDateTime>
#include <QTextStream>

#include <Parser.h>
#include <Headline.h>
#include <Clock.h>
#include <Exception.h>
#include <TimeInterval.h>

#include "TestHelpers.h"

using namespace OrgMode;

const QDate today(2015, 4, 24);
const QDateTime six(today, QTime(6,0));
const QDateTime seven(today, QTime(7,0));
const QDateTime eight(today, QTime(8,0));
const QDateTime nine(today, QTime(9,0));
const TimeInterval sixToEight(six, eight);
const TimeInterval sevenToNine(seven, nine);
const TimeInterval sevenToEight(seven, eight);
const TimeInterval toEight(QDateTime(), eight);
const TimeInterval fromSeven(seven);
const TimeInterval fromEight(eight);
const TimeInterval toSeven(QDateTime(), seven);
const TimeInterval sixToSeven(six, seven);
const TimeInterval eightToNine(eight, nine);
const TimeInterval eightToEight(eight, eight);
const TimeInterval sevenToSeven(seven, seven);
const TimeInterval eightToSeven(eight, seven); //invalid!

Q_DECLARE_METATYPE(TimeInterval);

class ClockTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testTimeIntervals_data();
    void testTimeIntervals();
    void testTimeIntervalsIsValid_data();
    void testTimeIntervalsIsValid();
    void testTimeIntervalDurations_data();
    void testTimeIntervalDurations();
    void testAccumulateForDay();
    void testAccumulateForWeek();
};

void ClockTests::testTimeIntervals_data()
{
    QTest::addColumn<TimeInterval>("left");
    QTest::addColumn<TimeInterval>("right");
    QTest::addColumn<TimeInterval>("intersection");
    QTest::newRow("1: two closed intervals that overlap") << sixToEight << sevenToNine << sevenToEight;
    QTest::newRow("1: two closed intervals that overlap, reversed") << sevenToNine << sixToEight << sevenToEight;
    QTest::newRow("2: one side open intervals") << toEight << fromSeven << sevenToEight;
    QTest::newRow("2: one side open intervals, reversed") << fromSeven << toEight << sevenToEight;
    QTest::newRow("3: two intervals open on the same side, open end") << fromSeven << fromEight << fromEight;
    QTest::newRow("3: two intervals open on the same side, open end, reversed") << fromEight << fromSeven << fromEight;
    QTest::newRow("3: two intervals open on the same side, open start") << toEight << toSeven << toSeven;
    QTest::newRow("3: two intervals open on the same side, open start, reversed") << toSeven << toEight << toSeven;
    QTest::newRow("4: non-intersecting intervals") << sixToSeven << eightToNine << eightToEight;
    QTest::newRow("4: non-intersecting intervals, reversed") << eightToNine << sixToSeven << eightToEight;
    QTest::newRow("5: intersection with an unbound interval") << sixToSeven << TimeInterval() << sixToSeven;
    QTest::newRow("5: intersection with an unbound interval, reversed") << TimeInterval() << sixToSeven << sixToSeven;
    QTest::newRow("5: intersection of two unbound intervals") << TimeInterval() << TimeInterval() << TimeInterval();
    QTest::newRow("6: touching, but non-intersecting intervals") << sixToSeven << sevenToEight << sevenToSeven;
    QTest::newRow("6: touching, but non-intersecting intervals, reversed") << sevenToEight << sixToSeven << sevenToSeven;
}

void ClockTests::testTimeIntervals()
{
    QFETCH(TimeInterval, left);
    QFETCH(TimeInterval, right);
    QFETCH(TimeInterval, intersection);
    QCOMPARE(left.intersection(right), intersection);
}

void ClockTests::testTimeIntervalsIsValid_data()
{
    QTest::addColumn<TimeInterval>("interval");
    QTest::addColumn<bool>("valid");

    QTest::newRow("seven to eight")    << sevenToEight     << true;
    QTest::newRow("eight to seven")    << eightToSeven     << false;
    QTest::newRow("eight to eight")    << eightToEight     << true;
    QTest::newRow("to eight")          << toEight          << true;
    QTest::newRow("from eight")        << fromEight        << true;
    QTest::newRow("open interval")     << TimeInterval()   << true;
}

void ClockTests::testTimeIntervalsIsValid()
{
    QFETCH(TimeInterval, interval);
    QFETCH(bool, valid);
    QCOMPARE(interval.isValid(), valid);
}

void ClockTests::testTimeIntervalDurations_data()
{
    QTest::addColumn<TimeInterval>("interval");
    QTest::addColumn<int>("duration");

    QTest::newRow("empty interval")    << sevenToSeven     << 0;
    QTest::newRow("eight to nine")     << eightToNine      << 60 * 60; // one hour
    QTest::newRow("from eight")        << fromEight        << std::numeric_limits<int>::max();
    QTest::newRow("to eight")          << toEight          << std::numeric_limits<int>::max();
    QTest::newRow("open interval")     << TimeInterval()   << std::numeric_limits<int>::max();
}

void ClockTests::testTimeIntervalDurations()
{
    QFETCH(TimeInterval, interval);
    QFETCH(int, duration);
    QCOMPARE(interval.duration(), duration);
}

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
        QCOMPARE(clock.duration(TimeInterval(mar26, mar27)), 60 * 60); //60 minutes on March 26
    } catch(Exception& ex) {
        QFAIL(qPrintable(ex.message()));
    }
}

void ClockTests::testAccumulateForWeek()
{
}

QTEST_APPLESS_MAIN(ClockTests)

#include "tst_ClockTests.moc"
