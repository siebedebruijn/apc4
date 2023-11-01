cmake_minimum_required(VERSION 3.17)
project(apc_ds LANGUAGES CXX VERSION 1.1.0)

option(ENABLE_ADDRESS_SANITIZER "Enable address sanitizer globally" ON)
option(ENABLE_UNDEFINED_SANITIZER "Enable undefined behavior sanitizer globally" ON)

add_subdirectory(lib_ds)
add_subdirectory(tests)
