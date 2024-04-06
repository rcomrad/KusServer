message("A'm inside")

# project(KusServerSource)

file(GLOB true helloworld_SRC
     CONFIGURE_DEPENDS    
     "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
     "${CMAKE_CURRENT_LIST_DIR}/*.h"
)

FOREACH(child ${helloworld_SRC})
     message("---->>> ${child}")
     IF(IS_DIRECTORY ${curdir}/${child})
          LIST(APPEND dirlist ${child})
     ENDIF()
ENDFOREACH()

# add_executable(helloworld ${helloworld_SRC})
