project(bird_chirp.core)


add_library(bird_chirp.core SHARED
		src/base_mail_receiver.cc
		../client/src/receiver_pop3.cc
		)

target_compile_definitions(bird_chirp.core PUBLIC ASIO_STANDALONE)

target_include_directories(bird_chirp.core PUBLIC
		../logging/include
		../tools/include
		)

target_link_libraries(bird_chirp.core PRIVATE
		fmt
		spdlog
		pthread
		ssl
		crypto)