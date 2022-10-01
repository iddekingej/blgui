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
    Gui
    Core    
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS        
    CoreAddons      
    I18n            
    WidgetsAddons   
    Config
 
)




set(blgui_LIBS
    Qt5::Widgets
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::I18n
 )
 
KI18N_WRAP_UI(blgui_ui_h ${blgui_ui})
ki18n_install(po)
qt5_add_resources(blgui_rcc_h ${blgui_RESOURCES})
add_definitions(-DKDE5)
