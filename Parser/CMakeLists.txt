# The OrgMode parser library
set(OrgModeParser_LIB_SRCS
        Parser.cpp
        Writer.cpp
        Exception.cpp
        OrgFileContent.cpp
# Classes that represent different OrgElements:
        OrgElement.cpp
        OrgFile.cpp
        Drawer.cpp
        DrawerEntry.cpp
        PropertyDrawer.cpp
        PropertyDrawerEntry.cpp
        DrawerClosingEntry.cpp
        OrgLine.cpp
        AttributeLine.cpp
        FileAttributeLine.cpp
        Headline.cpp
        ClockLine.cpp
        CompletedClockLine.cpp
# Classes that process OrgElements as visitors:
        Clock.cpp
        Tags.cpp
        Attributes.cpp
        Property.cpp
        Properties.cpp
)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
add_library(OrgModeParser SHARED ${OrgModeParser_LIB_SRCS})
generate_export_header(OrgModeParser)
target_link_libraries(OrgModeParser PUBLIC Qt5::Core)
target_include_directories(OrgModeParser PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(OrgModeParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS OrgModeParser DESTINATION lib)
