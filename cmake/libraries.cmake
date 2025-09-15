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

macro(vulkan_lib)
    find_package(Vulkan REQUIRED)
    target_link_libraries(${TARGET} PRIVATE Vulkan::Vulkan)
endmacro()
macro(crow_lib TARGET)
    find_package(Crow CONFIG REQUIRED)         
    target_link_libraries(${TARGET} PRIVATE Crow::Crow) 
endmacro()

macro(glfw_lib)
    find_package(glfw3 CONFIG REQUIRED)
    target_link_libraries(${TARGET} PRIVATE glfw)
endmacro()

# PRODUSES:
#   LIBRARY_NAME
#   TARGET

macro(lib_router)
    if(${LIBRARY_NAME} STREQUAL gtest)
        gtest_lib()
    elseif(${LIBRARY_NAME} STREQUAL postgresql)
        # Not implemented
    elseif(${LIBRARY_NAME} STREQUAL crow)
        crow_lib()
    elseif(${LIBRARY_NAME} STREQUAL mailio)
        # Not implemented
    elseif(${LIBRARY_NAME} STREQUAL boost)
        # Not implemented
    elseif(${LIBRARY_NAME} STREQUAL vulkan)
        vulkan_lib()
    elseif(${LIBRARY_NAME} STREQUAL glfw)
        glfw_lib()
    else()
        message(FATAL_ERROR "Unsupported library name '${LIBRARY_NAME}'!")
    endif()
endmacro()
