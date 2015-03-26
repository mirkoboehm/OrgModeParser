#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QtDebug>

#include "ClockTimeSummary.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(a.translate("main", "OrgModeParser clock time demo"));
    QCoreApplication::setApplicationVersion(a.translate("main", "1.0"));

    QCommandLineParser parser;
    parser.setApplicationDescription(a.translate("main", "Clock time demo for the OrgModeParser."));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(a);
    ClockTimeSummary clocktime(parser.positionalArguments());
    const int secondsClockedToday = clocktime.secondsClockedToday();
    const int hours = secondsClockedToday / 3600;
    const int minutes = (secondsClockedToday - hours*3600) / 60;
    const int secondsClockedThisWeek = clocktime.secondsClockedThisWeek();
    const int whours = secondsClockedThisWeek / 3600;
    const int wminutes = (secondsClockedThisWeek - whours*3600) / 60;
    const QString clockedTime(a.translate("main", "%1:%2 | %3:%4")
            .arg(hours, 2, 10, QChar::fromLatin1(' '))
            .arg(minutes, 2, 10, QChar::fromLatin1('0'))
            .arg(whours, 2, 10, QChar::fromLatin1(' '))
            .arg(wminutes, 2, 10, QChar::fromLatin1('0')));
    wcout << clockedTime.toStdWString();
}
