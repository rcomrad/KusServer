# REQUIERS:
#   TARGET - name of target for sources inclusion

macro(collect_src)
    file(GLOB_RECURSE
        project_sources
        ${CMAKE_CURRENT_LIST_DIR}/*.cpp
        ${CMAKE_CURRENT_LIST_DIR}/*.hpp
    )

    if (NOT ${IS_TEST})
        list(FILTER project_sources EXCLUDE REGEX "_tests/*")
        # if (${TARGET} MATCHES "kernel")
        #     list(FILTER project_sources EXCLUDE REGEX "tester/*")
        # endif()
    endif()
    
    target_include_directories(${TARGET} PUBLIC "sources/")
    target_sources(${TARGET} PRIVATE ${project_sources})
endmacro()

macro(get_subdirectory_list RESULT_VAR DIR)
    file(GLOB OBJ_LIST LIST_DIRECTORIES true ${DIR}/*)

    set(RESULT "")
    foreach(OBJ ${OBJ_LIST})
        if(IS_DIRECTORY ${curdir}/${OBJ})
            list(APPEND RESULT ${OBJ})
        endif()
    endforeach()

    set(${RESULT_VAR} ${RESULT})
endmacro()
