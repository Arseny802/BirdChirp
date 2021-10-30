#include "pch.h"
#include "../include/receiver_pop3.h"

namespace BirdChirp::Core {
receiver_pop3::receiver_pop3(const setup &settings) : base_mail_receiver(settings){

}

receiver_pop3::~receiver_pop3() = default;

bool receiver_pop3::Authorize() {
  return RunUser() && RunPass();
}

bool receiver_pop3::RunUser() {
  std::string command = fmt::format("USER {}", settings_.login);
  return SendRequest(command);
}

bool receiver_pop3::RunPass() {
  std::string command = fmt::format("PASS {}", settings_.password);
  return SendRequest(command);
}

int receiver_pop3::GetMessagesAmount() {
  return 0;
}

bool receiver_pop3::RunStat() {
  return SendRequest("STAT");
}

bool receiver_pop3::RunList(uint64_t message_index) {
  if (message_index) {
	std::string command = fmt::format("LIST {}", message_index);
	return SendRequest(command);
  }

  return SendRequest("LIST");
}

bool receiver_pop3::RunTop(uint64_t message_index, uint64_t rows_amount) {
  std::string command = fmt::format("TOP {} {}", message_index, rows_amount);
  return SendRequest(command);
}

bool receiver_pop3::RunRetrieve(uint64_t message_index) {
  std::string command = fmt::format("RETR {}", message_index);
  return SendRequest(command);
}

bool receiver_pop3::RunDelete(uint64_t message_index) {
  std::string command = fmt::format("DELE {}", message_index);
  return SendRequest(command);
}

bool receiver_pop3::RunApop() {
  return SendRequest("APOP");
}

bool receiver_pop3::RunNoop() {
  return SendRequest("NOOP");
}

bool receiver_pop3::RunReset() {
  return SendRequest("RSET");
}

bool receiver_pop3::RunQuit() {
  return SendRequest("QUIT");
}
} // namespace BirdChirp::Core
