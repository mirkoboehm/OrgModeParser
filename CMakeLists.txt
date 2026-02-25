cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(OrgModeParser)

include(GenerateExportHeader)
find_package(Qt5Core 5.3.0 REQUIRED NO_MODULE)
enable_testing()
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Git REQUIRED)
execute_process(COMMAND ${GIT_EXECUTABLE} describe --always --dirty --tags --abbrev=7
    RESULT_VARIABLE GIT_RESULT
    OUTPUT_VARIABLE OrgModeParser_VERSION
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE)
if(GIT_RESULT EQUAL 0)
    message(STATUS "Building OrgModeParser version ${OrgModeParser_VERSION}.")
else()
    message(FATAL_ERROR "Cannot determine OrgModeParser version from git!")
endif()

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_compile_definitions(QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII)
add_subdirectory(Parser)
add_subdirectory(AutoTests)
add_subdirectory(Demos/TODOCounter)
add_subdirectory(Tools/ClockTimeSummary)

