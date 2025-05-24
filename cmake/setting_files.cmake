macro(load_build_config_file)
    message("\n\nBUILD CONFIG-----------------------------")
    set(CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.cmake")
    message("\tSearch project build configuration file by path: '${CONFIG_FILE}'.")

    #TODO: fix 'Not searching for unused variables given on the command line.'
    if(NOT EXISTS "${CONFIG_FILE}")
        message("\tFile not found.")
        message("\tPopulating project build configuration file.")
        file(WRITE "${CONFIG_FILE}"
            "set(VCPKG_ROOT /home/user/vcpkg)\n"
            "set(TASK kernel)\n"
        )
    else()
        message("\tProject build configuration file found.")
    endif()

    include("${CONFIG_FILE}")
    message("\tSearch for vcpkg by path: '${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake'.")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    message("-----------------------------------------\n\n")
endmacro()

macro(load_target_switch_file)
    message("\n\nTARGET SWITCH----------------------------")
    set(TARGET_SWITCH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_target_switch.cmake")
    message("\tSearch the target switch cmake script by path: '${TARGET_SWITCH}'.")

    if(NOT EXISTS ${TARGET_SWITCH})
        message("\tFile not found.")
        message("\tPopulating the target switch cmake script.")
        
        get_subdirectory_list(SUBDIRS sources)

        file(WRITE ${TARGET_SWITCH} 
            "macro(check NAME)\n"
            "    if(\$\{TASK\} MATCHES \$\{NAME\} OR \$\{TASK\} MATCHES all)\n"
            "        include(\$\{CMAKE_CURRENT_SOURCE_DIR\}/sources/\$\{NAME\}/_setup.cmake)\n"
            "    endif()\n"
            "    set(\$\{NAME\}_MODULES \$\{MODULES\})\n"
            "    unset(MODULES)\n"
            "\n"
            "    foreach(MODULE \$\{\$\{NAME\}_MODULES\})\n"
            "        include(\$\{CMAKE_CURRENT_SOURCE_DIR\}/sources/\$\{MODULE\}/_setup.cmake)\n"
            "    endforeach()\n"
            "endmacro()\n"
            "\n"
            "check(_test)\n"
            "check(engine)\n"
            "check(kernel)\n"
            "check(ontology)\n"
            "check(server)\n"
        )

        #TODO: spaces in file path?
        message("\tFound:")
        foreach(DIR ${SUBDIRS})
            message("\t\t${DIR}")
            get_filename_component(DIR_NAME ${DIR} NAME) 
            file(APPEND ${TARGET_SWITCH} 
                "check(${DIR_NAME})\n"
            )
        endforeach()
    else()
        message("\tTarget switch cmake script found.")
    endif()

    message("-----------------------------------------\n\n")

    include("${TARGET_SWITCH}")
endmacro()
