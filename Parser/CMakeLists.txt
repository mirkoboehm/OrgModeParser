# The OrgMode parser library
set(OrgModeParser_LIB_SRCS
        Parser.cpp
        Headline.cpp
)

add_library(OrgModeParser ${OrgModeParser_LIB_SRCS})
generate_export_header(OrgModeParser BASE_NAME OrgModeParser)
target_link_libraries(OrgModeParser PUBLIC Qt5::Core)
