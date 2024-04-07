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

    get_filename_component(module_name ${module} NAME)

    add_library(${module_name} ${module_src})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${module_name})
    target_include_directories(${module_name} PRIVATE "sources/")

    # TODO: remove
    target_link_libraries(${module_name} PRIVATE libpqxx::pqxx)
    target_link_libraries(${module_name} PRIVATE Crow::Crow)
    target_link_libraries(${module_name} PRIVATE ${Boost_LIBRARIES})
    target_link_libraries(${module_name} PRIVATE mailio)
ENDFOREACH()
