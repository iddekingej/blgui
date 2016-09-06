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
set(bdgui_LIBS
    Qt5::Widgets
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::I18n
 )
 
 KI18N_WRAP_UI(bdgui_ui_h ${bdgui_ui})

qt5_add_resources(bdgui_rcc_h ${bdgui_RESOURCES})
add_definitions(-DKDE5)