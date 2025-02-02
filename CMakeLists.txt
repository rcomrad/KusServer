#-------------------------------------------------------------------------------
#                                   Project setup
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.21.3)

include(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_path.cmake)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(KusSysteam)
# project(KusSystem)

#-------------------------------------------------------------------------------
#                              Detect operating system
#-------------------------------------------------------------------------------

if (${MSVC})
    set(OS "BILL_WINDOWS")
else()
    set(OS "LINUS_LINUX")
endif()

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
    target_link_libraries(${EXE_NAME} PRIVATE libpqxx::pqxx)
    target_link_libraries(${EXE_NAME} PRIVATE Crow::Crow)
    target_link_libraries(${EXE_NAME} PRIVATE ${Boost_LIBRARIES})
    target_link_libraries(${EXE_NAME} PRIVATE Vulkan::Vulkan)
    # target_link_libraries(${EXE_NAME} PRIVATE Vulkan::glslang)
    # target_link_libraries(${EXE_NAME} PRIVATE Vulkan::dxc)
    # target_link_libraries(${EXE_NAME} PRIVATE mailio)

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
find_package(libpqxx CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)
find_package(Boost REQUIRED system filesystem)
find_package(GTest CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

# Sources include
add_executable(${PROJECT_NAME} "sources_main/main.cpp")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
create_exe(${PROJECT_NAME})

set(TEST_EXE_NAME "${PROJECT_NAME}_test")
add_executable(${TEST_EXE_NAME} "sources_main/test_main.cpp")
target_compile_features(${TEST_EXE_NAME} PRIVATE cxx_std_23)
target_include_directories("${PROJECT_NAME}_test" PUBLIC "sources_test/")
create_exe(${TEST_EXE_NAME})
include(sources_test/sources.cmake)

target_link_libraries(${TEST_EXE_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)