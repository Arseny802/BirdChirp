project(bird_chirp.utility)

add_executable(
		bird_chirp.utility
		src/bird_chirp.cc
)

target_include_directories(bird_chirp.utility PUBLIC
		../logging/include
		../core/include
		../client/include)

target_link_libraries(bird_chirp.utility
		bird_chirp.logging
		bird_chirp.core
		bird_chirp.client
		crypto
		fmt
		spdlog)
