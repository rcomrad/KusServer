#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.21.3)

if(NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT "D:/lib/vcpkg")
endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(Server)

#--------------------------------------------------------------------------------

# OS detection
if (${MSVC})
    set(OS "BILL_WINDOWS")
else()
    set(OS "LINUS_LINUX")
endif()
message(-----> ${OS})

#--------------------------------------------------------------------------------

# Compile options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries include
find_package(libpqxx CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)

# Sources include
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_scripts/cmake_scripts.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/sources/sources.cmake)
get_sources(SOURCES_LIST ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources)

#  Compiler defenitions
if    (${OS} MATCHES "LINUS_LINUX")
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUS_LINUX)
elseif(${OS} MATCHES "BILL_WINDOWS")
    target_compile_definitions(${PROJECT_NAME} PRIVATE BILL_WINDOWS)
endif()

# Libraries include
target_link_libraries(${PROJECT_NAME} PRIVATE libpqxx::pqxx)
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow)

# Output file name settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<0:>)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .exe)

#--------------------------------------------------------------------------------
