file(GLOB_RECURSE
    project_sources
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.hpp
)
list(FILTER project_sources EXCLUDE REGEX "database")
# list(FILTER project_sources EXCLUDE REGEX "ontology")
target_sources(${EXE_NAME} PRIVATE ${project_sources})

# set(filtered_sources)
# foreach(source ${project_sources})
#     if(NOT "${source}" MATCHES "/(ontology|database)/")
#         list(APPEND filtered_sources ${source})
#     endif()
# endforeach()

# target_sources(${EXE_NAME} PRIVATE ${filtered_sources})
