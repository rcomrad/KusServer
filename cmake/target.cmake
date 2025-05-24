# include(glob.cmake)

#-------------------------------------------------------------------------------
# Set output extension and path
#-------------------------------------------------------------------------------

# PRODUSES:
#   TARGET

macro(set_output_folder)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY 
        ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
endmacro()

macro(set_output_folder_and_exe)
    set_output_folder()
    set_target_properties(${TARGET} PROPERTIES SUFFIX .exe)
endmacro()

#-------------------------------------------------------------------------------
# Create target
#-------------------------------------------------------------------------------

# REQUIERS:
#   TARGET_BASE_NAME - name of target for sources inclusion
#   IS_EXECUTABLE - 
#   IS_TEST - 

# PRODUSES:
#   TARGET

macro(create_target)
    set(TARGET "${TARGET_BASE_NAME}") 
    if (${IS_TEST}) # tests cannot be library
        set(TARGET "${TARGET}_test") # for tests we have '_test' postfix

        add_executable(${TARGET} "sources/main_test.cpp")

        # add test files to its target
        target_compile_definitions(${TARGET} PRIVATE TESTING)
        target_sources(${TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/_tests)
        set_output_folder_and_exe()
    elseif  (${IS_EXECUTABLE})
        add_executable(${TARGET} "sources/main_app.cpp")
        set_output_folder_and_exe()
    else()
        add_library(${TARGET})
        set_output_folder()
    endif()
    
    set_target_flags(${TARGET})
endmacro()

#-------------------------------------------------------------------------------

# REQUIERS:
#   DEPENDANTS - 
#   LIBRARIES - 
#   IS_EXECUTABLE - 
#   IS_TESTS - 

# INHERENTS? IS_EXECUTABLE

# PRODUSES:
#   TARGET_BASE_NAME
#   IS_TEST

macro(create_module MODULE_TYPE)   
    if      (${MODULE_TYPE} MATCHES "EXECUTABLE")
        set(IS_EXECUTABLE TRUE)
    elseif  (${MODULE_TYPE} MATCHES "LIBRARY")
        set(IS_EXECUTABLE FALSE)
    else()
        message(FATAL_ERROR "\n!!!!!!!!!!!! ---> ERROR <--- !!!!!!!!!!!!\n"
                "---> Wrong target type! "
                "Expected 'EXECUTABLE' or 'LIBRARY'. "
                "But '${MODULE_TYPE}' was found.\n")
    endif()

    set(SOURCES_PATH ${CMAKE_CURRENT_LIST_DIR})
    get_filename_component(TARGET_BASE_NAME ${SOURCES_PATH} NAME)

    foreach(IS_TEST FALSE TRUE)
        create_target()
        collect_src()
        
        foreach(LIBRARY_NAME ${LIBRARIES})
            lib_router()
        endforeach()

        foreach(MODULE_NAME ${MODULES})
            target_link_libraries(${TARGET} PUBLIC ${MODULE_NAME})
        endforeach()

        set(LIBRARIES ${LIBRARIES} gtest)
    endforeach()
endmacro()

#-------------------------------------------------------------------------------
