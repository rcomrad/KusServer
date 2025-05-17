file(GLOB_RECURSE
    test_sources
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.hpp
)

target_sources(${EXE_NAME} PRIVATE ${test_sources})
target_include_directories(${EXE_NAME} PRIVATE "sources_test/")
