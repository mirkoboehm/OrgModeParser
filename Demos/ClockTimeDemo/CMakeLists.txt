# Build definition for the clock time demo:
add_executable(OrgModeParser_ClockTimeDemo ClockTimeDemo-main.cpp ClockTimeSummary.cpp)
target_link_libraries(OrgModeParser_ClockTimeDemo OrgModeParser)
set_target_properties(OrgModeParser_ClockTimeDemo PROPERTIES MACOSX_BUNDLE FALSE)
install(TARGETS OrgModeParser_ClockTimeDemo ${INSTALL_TARGETS_DEFAULT_ARGS})
