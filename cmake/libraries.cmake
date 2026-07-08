# PRODUSES:
#   TARGET

macro(boost_lib)
    find_package(Boost REQUIRED COMPONENTS preprocessor)
    target_link_libraries(${TARGET} PUBLIC Boost::preprocessor)
endmacro()

macro(crow_lib)
    find_package(Crow CONFIG REQUIRED)
    target_link_libraries(${TARGET} PUBLIC Crow::Crow asio::asio)
endmacro()

macro(freetype_lib)
    find_package(Freetype REQUIRED)
    target_link_libraries(${TARGET} PRIVATE Freetype::Freetype)
endmacro()

macro(glfw_lib)
    find_package(glfw3 CONFIG REQUIRED)
    target_link_libraries(${TARGET} PUBLIC glfw)
endmacro()

macro(glm_lib)
    find_package(glm CONFIG REQUIRED)
    target_link_libraries(${TARGET} PUBLIC glm::glm-header-only)
endmacro()

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
    target_link_libraries(${TARGET} PUBLIC libpqxx::pqxx)
endmacro()

macro(vulkan_lib)
    find_package(Vulkan REQUIRED)
    target_link_libraries(${TARGET} PUBLIC Vulkan::Vulkan)
    target_include_directories(${TARGET}  PRIVATE ${Vulkan_INCLUDE_DIRS})
endmacro()


# PRODUSES:
#   LIBRARY_NAME
#   TARGET

macro(lib_router)
    if(${LIBRARY_NAME} STREQUAL boost)
        boost_lib()
    elseif(${LIBRARY_NAME} STREQUAL crow)
        crow_lib()
    elseif(${LIBRARY_NAME} STREQUAL freetype)
        freetype_lib()
    elseif(${LIBRARY_NAME} STREQUAL glfw)
        glfw_lib()
    elseif(${LIBRARY_NAME} STREQUAL glm)
        glm_lib()
    elseif(${LIBRARY_NAME} STREQUAL gtest)
        gtest_lib()
    elseif(${LIBRARY_NAME} STREQUAL postgresql)
        postgresql_lib()
    elseif(${LIBRARY_NAME} STREQUAL vulkan)
        vulkan_lib()
    else()
        message(FATAL_ERROR "Unsupported library name '${LIBRARY_NAME}'!")
    endif()
endmacro()
