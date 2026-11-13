add_library(safe_integer
    src/safe_integer.c
)

target_include_directories(safe_integer PUBLIC src)

add_library(safe_copy
    src/safe_copy.c
)

target_include_directories(safe_copy PUBLIC src)

add_executable(safe_integer_demo
    main.c
)

target_link_libraries(safe_integer_demo PRIVATE safe_integer safe_copy)

add_executable(safe_copy_demo
    main.c
)

target_link_libraries(safe_copy_demo PRIVATE safe_copy safe_integer)

if(BUILD_TESTING)
    add_test(NAME safe_integer_demo_smoke COMMAND safe_integer_demo)

    add_executable(test_safe_integer
        tests/test_safe_integer.c
    )
    target_link_libraries(test_safe_integer PRIVATE safe_integer)
    add_test(NAME safe_integer_parser COMMAND test_safe_integer)

    add_executable(test_safe_copy
        tests/test_safe_copy.c
    )
    target_link_libraries(test_safe_copy PRIVATE safe_copy)
    add_test(NAME safe_copy_parser COMMAND test_safe_copy)
endif()