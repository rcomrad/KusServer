#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.21.3)

if(NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT "D:/lib/vcpkg")
    set(vcpkgRoot "D:/lib/vcpkg")
endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(Server)

#--------------------------------------------------------------------------------

# OS detection
# message("${MSVC}")
# message("${MSYS}")
# message("${UNIX}")
# message("${CMAKE_SYSTEM}")
# message("${CMAKE_SYSTEM_NAME}")
# message("${MSVC_VERSION}")
if (${MSVC})
    set(OS "BILL_WINDOWS")
else()
    set(OS "LINUS_LINUX")
endif()
message(-----> ${OS})

#--------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
# Compile options
# set(CROW_FEATURES ssl)
# if (${OS} MATCHES "LINUS_LINUX")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wl,--no-as-needed -ldl")
# elseif(${OS} MATCHES "BILL_WINDOWS")
#     add_compile_options("/std:c++latest")
# endif()

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
if (${OS} MATCHES "LINUS_LINUX")
    # target_include_directories(${PROJECT_NAME} PUBLIC ${VCPKG_ROOT}/installed/x64-linux/include)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUS_LINUX)
    # target_compile_definitions(${PROJECT_NAME} CROW_ENABLE_SSL)
elseif(${OS} MATCHES "BILL_WINDOWS")
    # target_include_directories(${PROJECT_NAME} PUBLIC ${VCPKG_ROOT}/installed/x64-windows/include)
    target_compile_definitions(${PROJECT_NAME} PRIVATE BILL_WINDOWS)

    # message(---> ${VCPKG_ROOT}/installed/x64-windows/include)
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
