#--------------------------------------------------------------------------------

macro(get_sources SOURCE_LIST DIR)

    set(FOLDER_NAMES 

    code 
    core 
    database 
    domain
    general_tools
    get 
    module 
    multitool 
    post 
    process 
    router 
    server 
    tester 
    tex_manager
    text_data
    
    )

    add_sources(${SOURCE_LIST} "${DIR}/sources" "${FOLDER_NAMES}")
endmacro()

#--------------------------------------------------------------------------------
