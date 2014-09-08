# The OrgMode parser library
set(OrgModeParser_LIB_SRCS
        Headline.cpp
)

add_library(OrgModeParser ${OrgModeParser_LIB_SRCS})
target_link_libraries(OrgModeParser PUBLIC Qt5::Core)
