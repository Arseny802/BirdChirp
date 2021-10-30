project(bird_chirp.utility)

add_executable(
		bird_chirp.utility
		src/bird_chirp.cc
)
target_include_directories(bird_chirp.utility PUBLIC
		../core/include)
target_link_libraries(bird_chirp.utility
		bird_chirp.core
		fmt
		spdlog)