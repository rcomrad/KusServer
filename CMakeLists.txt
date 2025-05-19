cmake_minimum_required(VERSION 3.21.3)

file(GLOB_RECURSE
    cmake_scripts
    ${CMAKE_CURRENT_LIST_DIR}/cmake/*
)

foreach(script ${cmake_scripts})
    include(${script})
endforeach()

flag_setup()

