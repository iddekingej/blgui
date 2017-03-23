project (bdgui)


set(KDE_VERSION ${kde})
set(RUN_TEST ${run_test})

if(KDE_VERSION EQUAL "4")
	cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
else()
	cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
endif()


set(bdgui_ui
	ui/main.ui 
	ui/fields.ui 
	ui/devinfo.ui 
	ui/parinfo.ui 
	ui/about.ui 
	ui/visibletabs.ui
	ui/mount.ui
	ui/newtab.ui
	ui/tabconfig.ui
	ui/usertabdef.ui
)

set(bdgui_RESOURCES 
	resources/icons.qrc
)

set(bdgui_SRCS   
	base/globals.cpp 
	base/linklist.cpp 
	base/utils.cpp
	base/config.cpp
	data/alias.cpp 	
	data/btrfs.cpp 
	data/changemanager.cpp
	data/devicealias.cpp 
	data/device.cpp 
	data/devicelist.cpp 
	data/mount.cpp
	data/mtab.cpp
	data/partition.cpp 
	data/devicebase.cpp 
	data/deviceinfo.cpp 
	data/raid.cpp 
	data/usb.cpp
	data/iscsi.cpp
	data/udevmonitor.cpp
	data/diskstat.cpp
	data/filesystems.cpp
	data/linuxraid.cpp
	data/pci.cpp
	data/tabdef.cpp
	data/lvm.cpp
	data/sortproxy.cpp
	gui/about.cpp
	gui/formparinfo.cpp 
	gui/formbasedevinfo.cpp 
	gui/formdevinfo.cpp 
	gui/fieldconfig.cpp 	
	gui/mainwindow.cpp 
	gui/visibletabs.cpp
	gui/mountdialog.cpp
	gui/formtabdef.cpp
	gui/formnewtab.cpp
	gui/usertabdef.cpp
	qjsonwrapper/Json.cpp
)

find_path(INC_BLKID blkid/blkid.h)
find_library(LIB_BLKID NAMES blkid)
if(NOT INC_BLKID OR NOT LIB_BLKID)
	message(FATAL_ERROR "Can't find blkid")
endif()

find_path(INC_UDEV libudev.h)
find_library(LIB_UDEV NAMES udev)
if(NOT INC_UDEV OR NOT LIB_UDEV)
	message(FATAL_ERROR "Can't find libudev")
endif()

if(KDE_VERSION EQUAL "4")
	include("kde4.cmake")
else()
	include("kde5.cmake")
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)


set(bdgui_SRCS ${bdgui_rcc_h} ${bdgui_SRCS} ${bdgui_ui_h})

add_executable(bdgui 	main.cpp ${bdgui_SRCS})


target_link_libraries(bdgui
    ${bdgui_LIBS}
    ${LIB_BLKID}    
    ${LIB_UDEV}
)



install(TARGETS bdgui  ${INSTALL_TARGETS_DEFAULT_ARGS})
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_subdirectory(po)

if(RUN_TEST EQUAL "1")
   include("bdgui_test.cmake")
endif()

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Gui for displaying block device information")
SET(CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})
SET(CPACK_RPM_PACKAGE_NAME "bdgui")
SET(CPACK_PACKAGE_VENDOR "iddekingej@lycos.com")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Readme.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "9.2")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_RPM_PACKAGE_VERSION "1")
SET(CPACK_RPM_PACKAGE_LICENSE "GPLv2.0")
SET(CPACK_RPM_PACKAGE_GROUP "Administration")
SET(CPACK_RPM_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION_SUMMARY})

include(CPack)
