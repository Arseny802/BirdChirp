project(bird_chirp.client)


add_library(bird_chirp.client SHARED
		src/receiver_pop3.cc
		)

target_include_directories(bird_chirp.client PUBLIC
		../logging/include
		../core/include)

target_link_libraries(bird_chirp.client
		bird_chirp.logging
		bird_chirp.core)