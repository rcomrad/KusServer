#--------------------------------------------------------------------------------

macro(get_sources SOURCE_LIST DIR)
    set(FOLDER_NAMES core database domain get post process tester)
    add_sources(${SOURCE_LIST} "${DIR}/sources" "${FOLDER_NAMES}")
endmacro()

#--------------------------------------------------------------------------------
