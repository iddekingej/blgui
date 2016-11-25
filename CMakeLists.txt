project (bdgui)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(KDE_VERSION ${kde})

#if(KDE_OPTION EQUAL "4")
#	message("bla")
#endif()


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
	ui/vginfo.ui
)

set(bdgui_RESOURCES 
	resources/icons.qrc
)

set(bdgui_SRCS   
	main.cpp 
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
	gui/vginfo.cpp
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
	include("cmake.kde4")
else()
	include("cmake.kde5")
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(bdgui_SRCS ${bdgui_rcc_h} ${bdgui_SRCS} ${bdgui_ui_h})

add_executable(bdgui ${bdgui_SRCS})


target_link_libraries(bdgui
    ${bdgui_LIBS}
    ${LIB_BLKID}    
    ${LIB_UDEV}
)


install(TARGETS bdgui  ${INSTALL_TARGETS_DEFAULT_ARGS})
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_subdirectory(po)
