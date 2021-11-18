#include "../../pch.h"
#include "strategy_pop3.h"
#include <receiver_pop3.h>
#include "../commands/commands_pop3.h"

namespace BirdChirp::Utility {
std::string StrategyPop3::RunCommand(uint32_t command_code) {
  BirdChirp::Core::receiver_pop3 receiver_pop3(running_setup_);

  std::vector<std::function<std::string(void)>> executing_commands;
  executing_commands.reserve(8);

  if (receiver_pop3.Connect() && receiver_pop3.Authorize()) {
	if (command_code & static_cast<uint32_t>(CommandsPop3::Stat)) {
	  executing_commands.emplace_back([&receiver_pop3]() {
		receiver_pop3.RunStat();
		return receiver_pop3.ReadResponse();
	  });
	}
	if (command_code & static_cast<uint32_t>(CommandsPop3::Top)) {
	  executing_commands.emplace_back([&receiver_pop3]() {
		receiver_pop3.RunTop();
		return receiver_pop3.ReadResponse();
	  });
	}
	if (command_code & static_cast<uint32_t>(CommandsPop3::Noop)) {
	  executing_commands.emplace_back([&receiver_pop3]() {
		receiver_pop3.RunNoop();
		return receiver_pop3.ReadResponse();
	  });
	}
	if (command_code & static_cast<uint32_t>(CommandsPop3::List)) {
	  executing_commands.emplace_back([&receiver_pop3]() {
		receiver_pop3.RunList();
		return receiver_pop3.ReadResponse();
	  });
	}
	if (command_code & static_cast<uint32_t>(CommandsPop3::Apop)) {
	  executing_commands.emplace_back([&receiver_pop3]() {
		receiver_pop3.RunApop();
		return receiver_pop3.ReadResponse();
	  });
	}
	if (command_code & static_cast<uint32_t>(CommandsPop3::Retr)) {
	  executing_commands.emplace_back([&receiver_pop3]() {
		receiver_pop3.RunRetrieve();
		return receiver_pop3.ReadResponse();
	  });
	}
	if (command_code & static_cast<uint32_t>(CommandsPop3::Dele)) {
	  executing_commands.emplace_back([&receiver_pop3]() {
		receiver_pop3.RunDelete();
		return receiver_pop3.ReadResponse();
	  });
	}
	if (command_code & static_cast<uint32_t>(CommandsPop3::Rset)) {
	  executing_commands.emplace_back([&receiver_pop3]() {
		receiver_pop3.RunReset();
		return receiver_pop3.ReadResponse();
	  });
	}
  }

  std::stringstream result;
  for (auto&& command : executing_commands) {
	result << command();
  }

  return result.str();
}
} // namespace BirdChirp::Utility
