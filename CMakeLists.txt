project(OrgModeParser)
cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
include(GenerateExportHeader)
find_package(Qt5Core 5.4.0 REQUIRED NO_MODULE)
enable_testing()
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Parser)
add_subdirectory(AutoTests)
add_subdirectory(Demos/ClockTimeDemo)

