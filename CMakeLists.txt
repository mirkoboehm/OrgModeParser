project(OrgModeParser)
cmake_minimum_required(VERSION 3.0.0)
include(GenerateExportHeader)
find_package(Qt5Core 5.4.0 REQUIRED NO_MODULE)
enable_testing()
set(CMAKE_AUTOMOC ON)
add_definitions(-std=c++11)

add_subdirectory(Parser)
add_subdirectory(AutoTests)
add_subdirectory(Demos/ClockTimeDemo)

