project(bird_chirp.configuration)

add_library(bird_chirp.configuration SHARED
		src/config_reader.cc
		)

target_include_directories(bird_chirp.configuration PUBLIC
		../logging/include
		../tools/include
		)

target_link_libraries(bird_chirp.configuration PRIVATE
		bird_chirp.tools
		bird_chirp.logging)