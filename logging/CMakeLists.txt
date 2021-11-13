project(bird_chirp.logging)

add_library(bird_chirp.logging STATIC
		src/base_logger.cc
		)

target_include_directories(bird_chirp.logging PUBLIC
		../tools/include
		)

target_link_libraries(bird_chirp.logging
		fmt
		spdlog)