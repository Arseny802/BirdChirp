cmake_minimum_required(VERSION 3.17)
project (BirdChirp VERSION 0.1.0)

# Common solution Setup.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# Solution dependencies download and build.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Solution projects.
add_subdirectory(tools)
add_subdirectory(logging)
add_subdirectory(configuration)
add_subdirectory(core)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(utility)
add_subdirectory(application)

install(TARGETS
		bird_chirp.utility
		bird_chirp.application
		DESTINATION installation_bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${BirdChirp_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${BirdChirp_VERSION_MINOR}")
include(CPack)