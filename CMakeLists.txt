project (bdgui)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS 
    Core    
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons      
    I18n            
    WidgetsAddons   
    Config
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

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
    

KI18N_WRAP_UI(bdgui_ui_h ui/main.ui ui/fields.ui ui/devinfo.ui ui/parinfo.ui ui/about.ui)

qt5_add_resources(bdgui_rcc_h resources/icons.qrc)

set(bdgui_SRCS   
	main.cpp 
	base/globals.cpp 
	base/linklist.cpp 
	base/utils.cpp
	data/devicealias.cpp 
	data/alias.cpp 	
	data/device.cpp 
	data/devicelist.cpp 
	data/mount.cpp
	data/mtab.cpp
	data/partition.cpp 
	data/devicebase.cpp 
	data/deviceinfo.cpp 
	data/raid.cpp 
	data/btrfs.cpp 
	data/udevmonitor.cpp
	gui/about.cpp
	gui/formparinfo.cpp 
	gui/formbasedevinfo.cpp 
	gui/formdevinfo.cpp 
	gui/fieldconfig.cpp 	
	gui/mainwindow.cpp 
)

set(bdgui_SRCS ${bdgui_rcc_h} ${bdgui_SRCS} ${bdgui_ui_h})

add_executable(bdgui ${bdgui_SRCS})


target_link_libraries(bdgui
    Qt5::Widgets
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::I18n
    ${LIB_BLKID}    
    ${LIB_UDEV}
)


install(TARGETS bdgui  ${INSTALL_TARGETS_DEFAULT_ARGS})
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_subdirectory(po)
