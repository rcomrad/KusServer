file(GLOB
    module_src
    CONFIGURE_DEPENDS    
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
)

target_sources(${EXE_NAME} PRIVATE ${module_src})
target_include_directories(${EXE_NAME} PRIVATE "sources_test/")
