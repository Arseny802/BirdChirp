#include "../../pch.h"
#include "strategy_pop3.h"
#include <receiver_pop3.h>

namespace BirdChirp::Utility {
std::string StrategyPop3::RunCommand(uint32_t command_code) {
  BirdChirp::Core::receiver_pop3 receiver_pop3(running_setup_);
  if (receiver_pop3.Connect() && receiver_pop3.Authorize()) {
	receiver_pop3.RunStat();
	//receiver_pop3.RunTop(1);
	std::string first_message;
	receiver_pop3.RunRetrieve(1, first_message);
	receiver_pop3.RunList();
	receiver_pop3.RunQuit();
  }
  return std::string();
}
} // namespace BirdChirp::Utility
