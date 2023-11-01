cmake_minimum_required(VERSION 3.18)

project(lib_ds LANGUAGES CXX)

set(lib_name lib_ds)

add_library(${lib_name} INTERFACE)

target_include_directories(${lib_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(${lib_name} INTERFACE cxx_std_20)

set_target_properties(${lib_name} PROPERTIES
        CXX_EXTENSIONS OFF
        )


set(dummy_exec_name dummy)
add_executable(${dummy_exec_name})
target_sources(${dummy_exec_name} PRIVATE dummy.cpp)

target_compile_options(${dummy_exec_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror>
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<CONFIG:Debug>:-O0 -g3 -fno-omit-frame-pointer>>
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<CONFIG:Release>:-O3>>
        )

message("Address sanitizer enabled for dummy: ${ENABLE_ADDRESS_SANITIZER}")
message("Undefined behavior sanitizer enabled for dummy: ${ENABLE_UNDEFINED_SANITIZER}")

target_compile_options(${dummy_exec_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<BOOL:${ENABLE_ADDRESS_SANITIZER}>:-fsanitize=address>>
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<BOOL:${ENABLE_UNDEFINED_SANITIZER}>:-fsanitize=undefined>>
        )

target_link_options(${dummy_exec_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<BOOL:${ENABLE_ADDRESS_SANITIZER}>:-fsanitize=address>>
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:$<$<BOOL:${ENABLE_UNDEFINED_SANITIZER}>:-fsanitize=undefined>>
)

target_compile_options(${dummy_exec_name} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Debug>:/RTC1 /Od /Zi>>
        $<$<CXX_COMPILER_ID:MSVC>:$<$<CONFIG:Release>:/O2>>
        )


target_link_libraries(${dummy_exec_name} ${lib_name})
        
