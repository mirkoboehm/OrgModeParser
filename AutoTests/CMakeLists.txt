enable_testing()
find_package(Qt5Test 5.4.0 REQUIRED NO_MODULE)

QT5_ADD_RESOURCES( TestDataResources_SRCS TestData.qrc )

########### next target ###############

set(ParserTests_SRCS tst_ParserTests.cpp ${TestDataResources_SRCS})
add_executable(OrgModeParser_ParserTests ${ParserTests_SRCS})
target_link_libraries(OrgModeParser_ParserTests Qt5::Test OrgModeParser)
target_include_directories(OrgModeParser_ParserTests PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_test(OrgModeParser_ParserTests OrgModeParser_ParserTests)
set_target_properties(OrgModeParser_ParserTests PROPERTIES MACOSX_BUNDLE FALSE)

