#--------------------------------------------------------------------------------

set(SCRIPT_NAMES add_sources check_file prepare_file download_archive prepare_lib)

foreach(SCRIPT IN LISTS SCRIPT_NAMES)
    include(${CMAKE_CURRENT_LIST_DIR}/${SCRIPT}.cmake)
endforeach()

#--------------------------------------------------------------------------------
