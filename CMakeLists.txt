cmake_minimum_required(VERSION 3.21)

project(embedded_security_learning VERSION 0.1.0 LANGUAGES C)

add_executable(embedded_security
    src/main.c
)

set_target_properties(embedded_security PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

if(MSVC)
    target_compile_options(embedded_security PRIVATE /W4)
else()
    target_compile_options(embedded_security PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

include(CTest)

if(BUILD_TESTING)
    add_test(NAME embedded_security_smoke COMMAND embedded_security)
endif()