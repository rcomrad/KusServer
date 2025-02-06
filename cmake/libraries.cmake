# PRODUSES:
#   TARGET

macro(gtest_lib)
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(${TARGET} PRIVATE
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
    )
endmacro()

# PRODUSES:
#   LIBRARY_NAME
#   TARGET

macro(lib_router)
    if(${LIBRARY_NAME} STREQUAL gtest)
        gtest_lib()
    elseif(${LIBRARY_NAME} EQUAL postgresql)
    elseif(${LIBRARY_NAME} EQUAL crow)
    elseif(${LIBRARY_NAME} EQUAL mailio)
    elseif(${LIBRARY_NAME} EQUAL boost)
    elseif(${LIBRARY_NAME} EQUAL vulkan)
    else()
        message(FATAL_ERROR "Unsupported library name '${LIBRARY_NAME}'!")
    endif()
endmacro()


