#--------------------------------------------------------------------------------

macro(add_sources SOURCE_LIST SOURCE_DIR SOURCE_FOLDERS)
    # TODO: why foreach doen't work with "${SOURCE_FOLDERS}"?
    set(list_var "${SOURCE_FOLDERS}") 
    foreach(FOLDER_NAME IN LISTS list_var)
        include(${SOURCE_DIR}/${FOLDER_NAME}/${FOLDER_NAME}_sources.cmake)

        string(TOUPPER ${FOLDER_NAME} UPPER_DIR_NAME)
        list(TRANSFORM ${UPPER_DIR_NAME}_SOURCES PREPEND
            ${SOURCE_DIR}/${FOLDER_NAME}/)

        list(APPEND ${SOURCE_LIST} ${${UPPER_DIR_NAME}_SOURCES})
    endforeach()
endmacro()

#--------------------------------------------------------------------------------
