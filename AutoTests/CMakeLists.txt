find_package(Qt5Test 5.2.0 REQUIRED NO_MODULE)

kde_enable_exceptions()

include(ECMAddTests)

QT5_ADD_RESOURCES( TestDataResources_SRCS TestData.qrc )

########### next target ###############

set(ParserTests_SRCS tst_ParserTests.cpp ${TestDataResources_SRCS})
ecm_add_test(${ParserTests_SRCS} TEST_NAME OrgModeParser_ParserTests LINK_LIBRARIES Qt5::Test OrgModeParser)
set_target_properties(OrgModeParser_ParserTests PROPERTIES MACOSX_BUNDLE FALSE)

