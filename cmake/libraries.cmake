# PRODUSES:
#   TARGET

macro(gtest_lib)
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(${TARGET} PUBLIC
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
    )
endmacro()

macro(postgresql_lib)
    find_package(libpqxx CONFIG REQUIRED)
    target_link_libraries(${TARGET} PUBLIC libpqxx::pqxx -Bdynamic)
endmacro()

macro(crow_lib)
    find_package(Crow CONFIG REQUIRED)
    target_link_libraries(${TARGET} PUBLIC Crow::Crow asio::asio)
endmacro()

macro(boost_lib)
    find_package(Boost REQUIRED COMPONENTS preprocessor)
    target_link_libraries(${TARGET} PUBLIC Boost::preprocessor)
endmacro()

macro(vulkan_lib)
    find_package(Vulkan REQUIRED)
    target_link_libraries(${TARGET} PUBLIC Vulkan::Vulkan)
endmacro()

macro(glfw_lib)
    find_package(glfw3 CONFIG REQUIRED)
    target_link_libraries(${TARGET} PUBLIC glfw)
endmacro()

# PRODUSES:
#   LIBRARY_NAME
#   TARGET

macro(lib_router)
    if(${LIBRARY_NAME} STREQUAL gtest)
        gtest_lib()
    elseif(${LIBRARY_NAME} STREQUAL postgresql)
        postgresql_lib()
    elseif(${LIBRARY_NAME} STREQUAL crow)
        crow_lib()
    elseif(${LIBRARY_NAME} STREQUAL mailio)
        # Not implemented
    elseif(${LIBRARY_NAME} STREQUAL boost)
        boost_lib()
    elseif(${LIBRARY_NAME} STREQUAL vulkan)
        vulkan_lib()
    elseif(${LIBRARY_NAME} STREQUAL glfw)
        glfw_lib()
    else()
        message(FATAL_ERROR "Unsupported library name '${LIBRARY_NAME}'!")
    endif()
endmacro()
