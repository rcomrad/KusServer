#--------------------------------------------------------------------------------

macro(get_sources SOURCE_LIST DIR)
    set(FOLDER_NAMES code core database domain file_data get multitool post process tester tex_manager)
    add_sources(${SOURCE_LIST} "${DIR}/sources" "${FOLDER_NAMES}")
endmacro()

#--------------------------------------------------------------------------------
