# download and populate Google Test from github
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

# for Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
message("Downloading googletest")

FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)


list(APPEND targets tests_custom tests_list tests_iterators )
list(APPEND sources custom_tests.cpp  list_tests.cpp list_iterator_tests.cpp)

list(LENGTH targets n_targets)
math(EXPR n_loop "${n_targets}-1")

foreach(ind RANGE ${n_loop})
    list(GET targets ${ind} test_exec_name)
    list(GET sources ${ind} tests_source)

    message(STATUS "Creating test target: ${test_exec_name}")


    add_executable(${test_exec_name} test_runner.cpp ${tests_source})

    target_compile_features(${test_exec_name} PRIVATE cxx_std_20)
    set_target_properties(${test_exec_name} PROPERTIES CXX_EXTENSIONS OFF)

    target_link_libraries(${test_exec_name} lib_ds)
    target_link_libraries(${test_exec_name} gtest_main gmock)
    gtest_discover_tests(${test_exec_name})

    target_compile_options(${test_exec_name} PRIVATE
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror>
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<CONFIG:Debug>:-O0 -g3 -fno-omit-frame-pointer>>
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<CONFIG:Release>:-O3>>
    )

    if (ENABLE_ADDRESS_SANITIZER)
        message("Enabling address sanitizer for ${test_exec_name}")
    endif(ENABLE_ADDRESS_SANITIZER)

    if (ENABLE_UNDEFINED_SANITIZER)
        message("Enabling undefined behavior sanitizer for ${test_exec_name}")
    endif(ENABLE_UNDEFINED_SANITIZER)

    target_compile_options(${test_exec_name} PRIVATE
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<BOOL:${ENABLE_ADDRESS_SANITIZER}>:-fsanitize=address>>
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<BOOL:${ENABLE_UNDEFINED_SANITIZER}>:-fsanitize=undefined>>
    )

    target_link_options(${test_exec_name} PRIVATE
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<BOOL:${ENABLE_ADDRESS_SANITIZER}>:-fsanitize=address>>
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<BOOL:${ENABLE_UNDEFINED_SANITIZER}>:-fsanitize=undefined>>
    )

    target_compile_options(${test_exec_name} PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W4>
            $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Debug>:/RTC1 /Od /Zi>>
            $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Release>:/O2>>
    )

endforeach()