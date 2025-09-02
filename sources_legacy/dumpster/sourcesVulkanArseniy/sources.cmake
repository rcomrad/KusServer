file(GLOB_RECURSE
    project_sources
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.hpp
)

target_sources(${EXE_NAME} PRIVATE ${project_sources})