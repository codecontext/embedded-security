find_package(OpenSSL REQUIRED COMPONENTS Crypto)

add_library(xor_cipher
    src/xor_cipher.c
)

target_include_directories(xor_cipher PUBLIC src)

add_library(caesar_cipher
    src/caesar_cipher.c
)

target_include_directories(caesar_cipher PUBLIC src)

add_library(sha256_digest
    src/sha256_digest.c
)

target_include_directories(sha256_digest PUBLIC src)
target_link_libraries(sha256_digest PUBLIC OpenSSL::Crypto)

add_executable(cryptography_demo
    main.c
)

target_link_libraries(cryptography_demo PRIVATE
    xor_cipher
    caesar_cipher
    sha256_digest
)

if(BUILD_TESTING)
    add_test(NAME xor_cipher_demo_smoke COMMAND cryptography_demo)
    add_test(
        NAME caesar_cipher_demo_smoke
        COMMAND cryptography_demo caesar
    )
    add_test(
        NAME sha256_digest_demo_smoke
        COMMAND cryptography_demo sha256
    )

    add_executable(test_xor_cipher
        tests/test_xor_cipher.c
    )
    target_link_libraries(test_xor_cipher PRIVATE xor_cipher)
    add_test(NAME xor_cipher_round_trip COMMAND test_xor_cipher)

    add_executable(test_caesar_cipher
        tests/test_caesar_cipher.c
    )
    target_link_libraries(test_caesar_cipher PRIVATE caesar_cipher)
    add_test(NAME caesar_cipher_round_trip COMMAND test_caesar_cipher)

    add_executable(test_sha256_digest
        tests/test_sha256_digest.c
    )
    target_link_libraries(test_sha256_digest PRIVATE sha256_digest)
    add_test(NAME sha256_digest_known_answers COMMAND test_sha256_digest)
endif()
