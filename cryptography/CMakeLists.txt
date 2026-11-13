add_library(xor_cipher
    src/xor_cipher.c
)

target_include_directories(xor_cipher PUBLIC src)

add_executable(xor_cipher_demo
    main.c
)

target_link_libraries(xor_cipher_demo PRIVATE xor_cipher)

if(BUILD_TESTING)
    add_test(NAME xor_cipher_demo_smoke COMMAND xor_cipher_demo)

    add_executable(test_xor_cipher
        tests/test_xor_cipher.c
    )
    target_link_libraries(test_xor_cipher PRIVATE xor_cipher)
    add_test(NAME xor_cipher_round_trip COMMAND test_xor_cipher)
endif()
