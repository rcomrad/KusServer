
#-------------------------------------------------------------------------------
#                                   Project setup
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.22.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_path.cmake)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
include("C:/vcpkg/scripts/buildsystems/vcpkg.cmake")


project(KusSysteam)



# project(KusSystem)

#-------------------------------------------------------------------------------
#                              Detect operating system
#-------------------------------------------------------------------------------

if (${MSVC})
    set(OS "BILL_WINDOWS")
    add_compile_options(/Zc:preprocessor /std:c++20)
    message("--> WINDOWS <---")
else()
    set(OS "LINUS_LINUX")
endif()

if(MSVC)
    add_compile_options(/Zc:__cplusplus)  # Для Visual Studio (MSVC)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#-------------------------------------------------------------------------------

macro(create_exe NAME)
    set(EXE_NAME ${NAME})
    target_include_directories(${EXE_NAME} PUBLIC "sources/")
    include(sources/sources.cmake)

    #  Compiler defenitions
    if    (${OS} MATCHES "LINUS_LINUX")
        target_compile_definitions(${EXE_NAME} PRIVATE
            LINUS_LINUX)
    elseif(${OS} MATCHES "BILL_WINDOWS")
        target_compile_definitions(${EXE_NAME} PRIVATE
            BILL_WINDOWS _WIN32_WINNT=0x0601)
    endif()

    # Libraries include
    # target_link_libraries(${EXE_NAME} PRIVATE libpqxx::pqxx)
    target_link_libraries(${EXE_NAME} PRIVATE glfw)
    target_link_libraries(${EXE_NAME} PRIVATE Vulkan::Vulkan)
    target_link_libraries(${EXE_NAME} PRIVATE Crow::Crow)
    target_link_libraries(${EXE_NAME} PRIVATE ${Boost_LIBRARIES})
    target_link_libraries(${EXE_NAME} PRIVATE glm::glm)
    target_include_directories(${EXE_NAME} PRIVATE ${Stb_INCLUDE_DIR})
    target_link_libraries(${EXE_NAME} PRIVATE nlohmann_json::nlohmann_json)



    # Output file name settings
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    set_target_properties(${EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY 
        ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
    set_target_properties(${EXE_NAME} PROPERTIES OUTPUT_NAME ${EXE_NAME})
    set_target_properties(${EXE_NAME} PROPERTIES SUFFIX .exe)
endmacro()

#-------------------------------------------------------------------------------
#                               Executable creation
#-------------------------------------------------------------------------------

# Compile options
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries include
# find_package(mailio CONFIG REQUIRED)
# find_package(libpqxx CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(Crow CONFIG REQUIRED)
find_package(Boost REQUIRED system filesystem)
find_package(Stb REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Sources include
add_executable(${PROJECT_NAME} "sources_main/main.cpp")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
# target_compile_options(${PROJECT_NAME} PRIVATE /std:c++20 /Zc:preprocessor)
create_exe(${PROJECT_NAME})

set(TEST_EXE_NAME "${PROJECT_NAME}_test")
add_executable(${TEST_EXE_NAME} "sources_main/test_main.cpp")
target_compile_features(${TEST_EXE_NAME} PRIVATE cxx_std_20)
# target_compile_options(${PROJECT_NAME} PRIVATE /std:c++20 /Zc:preprocessor)
target_include_directories("${PROJECT_NAME}_test" PUBLIC "sources_test/")
create_exe(${TEST_EXE_NAME})
include(sources_test/sources.cmake)

target_link_libraries(${TEST_EXE_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)