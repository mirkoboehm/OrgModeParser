project(OrgModeParser)
cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
include(GenerateExportHeader)
find_package(Qt5Core 5.4.0 REQUIRED NO_MODULE)
enable_testing()
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(Git REQUIRED)
EXECUTE_PROCESS(COMMAND ${GIT_EXECUTABLE} describe  --always --dirty --tags --abbrev=7
    RESULT_VARIABLE GIT_RESULT
    OUTPUT_VARIABLE OrgModeParser_VERSION
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE )
IF (GIT_RESULT EQUAL 0)
    MESSAGE("Building OrgModeParser version ${OrgModeParser_VERSION}.")
ELSE ()
    MESSAGE(FATAL_ERROR "Cannot determine OrgModeParser version from git!")
ENDIF ()

add_subdirectory(Parser)
add_subdirectory(AutoTests)
add_subdirectory(Demos/ClockTimeDemo)

