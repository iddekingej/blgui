file(GLOB _po_files *.po)
GETTEXT_PROCESS_PO_FILES(en ALL INSTALL_DESTINATION ${KDE_INSTALL_FULL_LOCALEDIR} PO_FILES ${_po_files} )
