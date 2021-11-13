project(bird_chirp.server)


add_library(bird_chirp.server SHARED
		src/imap_server.cc
		src/pop3_server.cc
		src/smtp_server.cc
		)