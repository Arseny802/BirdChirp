cmake_minimum_required(VERSION 3.17)
project (BirdChirp VERSION 0.1.0)

# Common solution setup.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")

# Solution dependencies download and build.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Solution projects.
add_subdirectory(logging)
add_subdirectory(core)
add_subdirectory(server/storage)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(utility)

