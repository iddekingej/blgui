cmake_policy(SET CMP0002 NEW)

find_package(Gettext REQUIRED)
if (NOT GETTEXT_MSGMERGE_EXECUTABLE)
MESSAGE(FATAL_ERROR "Please install msgmerge binary")
endif (NOT GETTEXT_MSGMERGE_EXECUTABLE)
if (NOT GETTEXT_MSGFMT_EXECUTABLE)
MESSAGE(FATAL_ERROR "Please install msgmerge binary")
endif (NOT GETTEXT_MSGFMT_EXECUTABLE)

add_subdirectory(nl)
add_subdirectory(en)
