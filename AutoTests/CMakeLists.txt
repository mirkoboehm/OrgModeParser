enable_testing()
find_package(Qt5Test 5.3.0 REQUIRED NO_MODULE)

qt5_add_resources(TestDataResources_SRCS TestData.qrc)

########### next target ###############

set(ParserTests_SRCS tst_ParserTests.cpp TestHelpers.cpp ${TestDataResources_SRCS})
add_executable(OrgModeParser_ParserTests ${ParserTests_SRCS})
target_link_libraries(OrgModeParser_ParserTests Qt5::Test OrgModeParser)
target_include_directories(OrgModeParser_ParserTests PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_test(OrgModeParser_ParserTests OrgModeParser_ParserTests)
set_target_properties(OrgModeParser_ParserTests PROPERTIES MACOSX_BUNDLE FALSE)
set_property(TARGET OrgModeParser_ParserTests PROPERTY CXX_STANDARD 11)

########### next target ###############

set(ClockTests_SRCS tst_ClockTests.cpp TestHelpers.cpp ${TestDataResources_SRCS})
add_executable(OrgModeParser_ClockTests ${ClockTests_SRCS})
target_link_libraries(OrgModeParser_ClockTests Qt5::Test OrgModeParser)
target_include_directories(OrgModeParser_ClockTests PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_test(OrgModeParser_ClockTests OrgModeParser_ClockTests)
set_target_properties(OrgModeParser_ClockTests PROPERTIES MACOSX_BUNDLE FALSE)
set_property(TARGET OrgModeParser_ClockTests PROPERTY CXX_STANDARD 11)

########### next target ###############

set(Benchmarks_SRCS tst_Benchmarks.cpp TestHelpers.cpp ${TestDataResources_SRCS})
add_executable(OrgModeParser_Benchmarks ${Benchmarks_SRCS})
target_link_libraries(OrgModeParser_Benchmarks Qt5::Test OrgModeParser)
target_include_directories(OrgModeParser_Benchmarks PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_test(OrgModeParser_Benchmarks OrgModeParser_Benchmarks)
set_target_properties(OrgModeParser_Benchmarks PROPERTIES MACOSX_BUNDLE FALSE)
set_property(TARGET OrgModeParser_Benchmarks PROPERTY CXX_STANDARD 11)
