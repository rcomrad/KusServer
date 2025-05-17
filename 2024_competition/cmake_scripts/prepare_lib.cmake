#--------------------------------------------------------------------------------

function(prepare_lib URL PATH FILE_NAMES FILE_HASHS)
    foreach(FILE IN LISTS FILE_NAMES)
        list (APPEND FILE_PATHS ${PATH}/${FILE})
    endforeach()

    get_corrupt_files(CORRUPT_FILE_NUMS "${FILE_PATHS}" "${FILE_HASHS}")

    list (LENGTH CORRUPT_FILE_NUMS SIZE)
    if(${SIZE})
        download_archive(${CMAKE_CURRENT_BINARY_DIR}/temp_lib ${URL})

        math(EXPR SIZE "${SIZE} - 1")
        foreach(I RANGE ${SIZE})
            list(GET CORRUPT_FILE_NUMS ${I} NUM)

            list(GET FILE_PATHS ${NUM} FILE_PATH)
            list(GET SQLITE_SOURCES ${NUM} FILE)

            message("Copy file ${FILE} to ${CMAKE_CURRENT_LIST_DIR}")
            file(COPY_FILE ${CMAKE_CURRENT_BINARY_DIR}/temp_lib/${FILE}
                ${FILE_PATH})
        endforeach()
    endif()
endfunction()

#--------------------------------------------------------------------------------
