add_executable(embedded_security
    main.c
)

if(BUILD_TESTING)
    add_test(NAME embedded_security_smoke COMMAND embedded_security)
endif()