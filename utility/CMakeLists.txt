project(bird_chirp.utility)

add_executable(bird_chirp.utility
		src/strategies/concrete_strategies/strategy_imap.cc
		src/strategies/concrete_strategies/strategy_pop3.cc
		src/strategies/concrete_strategies/strategy_smtp.cc
		src/strategies/base_strategy.cc
		src/strategies/strategy_factory.cc
		src/bird_chirp.cc
		src/pch.cc
)

target_include_directories(bird_chirp.utility PUBLIC
		../logging/include
		../core/include
		../server/include
		../client/include)

target_link_libraries(bird_chirp.utility
		bird_chirp.logging
		bird_chirp.core
		bird_chirp.client
		pthread
		crypto)
