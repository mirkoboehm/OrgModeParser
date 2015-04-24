#include <QString>
#include <QtTest>

#include <Parser.h>

#include "TestHelpers.h"

using namespace OrgMode;

class Benchmarks : public QObject
{
    Q_OBJECT

public:
    Benchmarks();

private Q_SLOTS:
    void benchmarkParseClocklines();
};

Benchmarks::Benchmarks()
{
}

void Benchmarks::benchmarkParseClocklines()
{
    const QString filename = FL1(":/Benchmarks/TestData/Benchmarks/BenchmarkClocklines.org");
    QFile orgFile(filename);
    QVERIFY(orgFile.open(QIODevice::ReadOnly));
    QTextStream stream(&orgFile);
    QBENCHMARK {
        Parser parser;
        const OrgElement::Pointer element = parser.parse(&stream, filename);
        Q_UNUSED(element);
    }
}

QTEST_APPLESS_MAIN(Benchmarks)

#include "tst_Benchmarks.moc"
