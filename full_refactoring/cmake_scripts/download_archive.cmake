#--------------------------------------------------------------------------------

set (DOWNLOAD_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/download)

function(download_archive TARGET_DIR ARCHIVE_URL)
    message("Downloading download_archive ${ARCHIVE_URL} to ${TARGET_DIR}")

    configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/downloader.cmake
                    ${DOWNLOAD_FOLDER}/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} .
                    WORKING_DIRECTORY ${DOWNLOAD_FOLDER})
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
                    WORKING_DIRECTORY ${DOWNLOAD_FOLDER})

    file(REMOVE_RECURSE ${DOWNLOAD_FOLDER})
endfunction()

#--------------------------------------------------------------------------------
