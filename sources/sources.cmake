file(GLOB
    module_folders
    CONFIGURE_DEPENDS    
    "${CMAKE_CURRENT_LIST_DIR}/*"
)

FOREACH(module ${module_folders})
    IF(NOT IS_DIRECTORY ${module})
        continue()
    ENDIF()

    file(GLOB
        module_src
        CONFIGURE_DEPENDS    
        "${module}/*.cpp"
        "${module}/*.hpp"
    )

    target_sources(${EXE_NAME} PRIVATE ${module_src})
ENDFOREACH()
