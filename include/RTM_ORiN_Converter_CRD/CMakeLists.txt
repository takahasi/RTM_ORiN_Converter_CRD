set(hdrs RTM_ORiN_Converter_CRD.h
    ManipulatorCommonInterface_CommonSVC_impl.h
    ManipulatorCommonInterface_MiddleLevelSVC_impl.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

