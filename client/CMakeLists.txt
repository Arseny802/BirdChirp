project(bird_chirp.client)


add_library(bird_chirp.client SHARED
		src/receiver_pop3.cc
		)