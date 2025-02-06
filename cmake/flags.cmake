macro(flag_setup)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    if (${MSVC})
        set(OS "BILL_WINDOWS")
        add_compile_options(/Zc:preprocessor /std:c++20)
    else()
        set(OS "LINUS_LINUX")
    endif()
endmacro()

macro(set_target_flags TARGET)
    if     (${OS} MATCHES "LINUS_LINUX")
        target_compile_definitions(${TARGET} PRIVATE
            LINUS_LINUX
        )
    elseif (${OS} MATCHES "BILL_WINDOWS")
        target_compile_definitions(${TARGET} PRIVATE
            BILL_WINDOWS
            _WIN32_WINNT=0x0601
        )
    endif()
    target_compile_features(${TARGET} PRIVATE cxx_std_20)
endmacro()
