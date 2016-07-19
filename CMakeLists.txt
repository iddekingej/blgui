project (ding)

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


feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
    

KI18N_WRAP_UI(ding_ui_h ui/main.ui ui/fields.ui ui/devinfo.ui ui/parinfo.ui ui/about.ui)

set(ding_SRCS   
	gui/about.cpp
	gui/formparinfo.cpp 
	gui/formbasedevinfo.cpp 
	data/devicealias.cpp data/alias.cpp 
	gui/formdevinfo.cpp 
	data/device.cpp 
	data/devicelist.cpp 
	data/mtabdevice.cpp 
	data/partition.cpp 
	data/devicebase.cpp 
	data/deviceinfo.cpp 
	dingui.cpp 
	gui/fieldconfig.cpp 
	base/globals.cpp 
	base/linklist.cpp 
	gui/mainwindow.cpp 
	data/raid.cpp 
	data/btrfs.cpp 
	base/utils.cpp)

set(ding_SRCS  ${ding_SRCS} ${ding_ui_h})

add_executable(ding ${ding_SRCS})


target_link_libraries(ding
    Qt5::Widgets
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::I18n
    ${LIB_BLKID}    
)


install(TARGETS ding  ${INSTALL_TARGETS_DEFAULT_ARGS})
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_subdirectory(po)
