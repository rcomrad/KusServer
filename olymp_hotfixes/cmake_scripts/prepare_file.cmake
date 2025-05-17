#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.21.3)

#--------------------------------------------------------------------------------

function(download_file PATH_TO_FILE URL FILE_HASH)
    message("Downloading file ${PATH_TO_FILE}")
    file(DOWNLOAD ${URL} ${PATH_TO_FILE} EXPECTED_HASH 
        ${CASH_TYPE}=${FILE_HASH})
endfunction()

function(prepare_file PATH_TO_FILE URL FILE_HASH)
    check_file(RESULT ${FILE_NAME} ${HASH})
    if(NOT ${RESULT})
        download_file(${FILE_NAME} ${URL} ${HASH})
    endif()
endfunction()

#--------------------------------------------------------------------------------
