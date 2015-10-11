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

#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QtDebug>

#include <Exception.h>
#include "ClockTimeSummary.h"
#include <Parser.h>

using namespace OrgMode;
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(a.translate("main", "OrgModeParser clock time summary"));
    QCoreApplication::setApplicationVersion(OrgMode::version());
    QCommandLineParser parser;
    try {
        parser.setApplicationDescription(a.translate("main", "Clock time summary tool, part of OrgModeParser."));
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
