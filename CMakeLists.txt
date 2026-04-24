cmake_minimum_required(VERSION 3.16)
project(TemplateCache)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(demo demo/main.cpp)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# ================= TESTS =================
add_executable(tests tests/test_cache.cpp)

target_link_libraries(tests
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
