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
        DrawerClosingEntry.cpp
        OrgLine.cpp
        AttributeLine.cpp
        FileAttributeLine.cpp
        Headline.cpp
        ClockLine.cpp
# Classes that process OrgElements as visitors:
        Clock.cpp
        Tags.cpp
        Properties.cpp
)

add_library(OrgModeParser ${OrgModeParser_LIB_SRCS})
generate_export_header(OrgModeParser BASE_NAME OrgModeParser)
target_link_libraries(OrgModeParser PUBLIC Qt5::Core)
