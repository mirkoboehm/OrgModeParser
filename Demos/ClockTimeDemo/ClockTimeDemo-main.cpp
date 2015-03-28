#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QtDebug>

#include <Exception.h>
#include "ClockTimeSummary.h"

using namespace OrgMode;
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(a.translate("main", "OrgModeParser clock time demo"));
    QCoreApplication::setApplicationVersion(a.translate("main", "1.0"));
    QCommandLineParser parser;
    try {
        parser.setApplicationDescription(a.translate("main", "Clock time demo for the OrgModeParser."));
        parser.addHelpOption();
        parser.addVersionOption();
        QCommandLineOption columnsOption(QStringList() << QStringLiteral("c") << QStringLiteral("columns"),
                                         a.translate("main", "Terminal columns."),
                                         a.translate("main", "columns"));
        QCommandLineOption promptModeOption(QStringList() << QStringLiteral("p") << QStringLiteral("promptmode"),
                                            a.translate("main", "Prompt mode (no newline at end)."));
        parser.addOption(columnsOption);
        parser.addOption(promptModeOption);
        parser.process(a);
        int columns;
        if (parser.isSet(columnsOption)) {
            bool ok;
            columns = parser.value(columnsOption).toInt(&ok);
            if (!ok) {
                throw RuntimeException(a.translate("main", "Columns argument needs to be an integer number!"));
            }
        } else {
            columns = 60;
        }
        const bool promptMode = parser.isSet(promptModeOption);
        ClockTimeSummary clocktime(parser.positionalArguments());
        clocktime.report(promptMode, columns);
    } catch (const RuntimeException& ex) {
        wcerr << "Error: " << ex.message().toStdWString() << endl
              << parser.helpText().toStdWString() << endl;
    }
}
