cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(main src/file-tape.cpp src/sort.cpp src/config.cpp src/main.cpp)

enable_testing()

find_package(GTest REQUIRED)

add_executable(tests test/test.cpp src/file-tape.cpp src/sort.cpp src/config.cpp)

target_link_libraries(tests GTest::GTest GTest::Main ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME AllTests COMMAND tests)

