#--------------------------------------------------------------------------------

set (CASH_TYPE MD5)

macro(check_file RESULT PATH_TO_FILE FILE_HASH)
    if (NOT EXISTS ${PATH_TO_FILE})
        message("File ${PATH_TO_FILE} doesn't exist")
        set(${RESULT} 0)
    else()
        file(${CASH_TYPE} ${PATH_TO_FILE} CURRENT_HASH) 
        string(COMPARE NOTEQUAL ${FILE_HASH} ${CURRENT_HASH} HASH_COMPARE)
        if(${HASH_COMPARE})
            message("File ${PATH_TO_FILE} corrupted")
            set(${RESULT} 0)
        else()
            message("File ${PATH_TO_FILE} checked")
            set(${RESULT} 1)
        endif()
    endif()
endmacro()

function(get_corrupt_files RESULT FILES HASHS)
    list (LENGTH FILES SIZE)
    math(EXPR SIZE "${SIZE} - 1")
    
    set(ANS)
    foreach(NUM RANGE ${SIZE})
        list(GET FILES ${NUM} FILE_PATH)
        list(GET HASHS ${NUM} HASH)

        check_file(FILE_CHECK ${FILE_PATH} ${HASH})
        if (NOT ${FILE_CHECK})
            LIST(APPEND ANS ${NUM})
        endif()
    endforeach()

    set(${RESULT} ${ANS} PARENT_SCOPE)
endfunction()

#--------------------------------------------------------------------------------
