#include "../../core/src/pch.h"
#include "../include/receiver_pop3.h"

namespace BirdChirp::Core {
receiver_pop3::receiver_pop3(const Setup &settings) : base_mail_receiver(settings){

}

receiver_pop3::~receiver_pop3() = default;

bool receiver_pop3::Authorize() {
  return RunUser() && RunPass();
}

bool receiver_pop3::RunUser() {
  std::string command = fmt::format("USER {}", settings_.login);
  if (SendRequest(command)) {
	std::string response = ReadResponse();
	return response.find("+OK") != std::string::npos;
  }

  return false;
}

bool receiver_pop3::RunPass() {
  std::string command = fmt::format("PASS {}", settings_.password);
  if (SendRequest(command)) {
	std::string response = ReadResponse();
	return response.find("+OK") != std::string::npos;
  }

  return false;
}

int receiver_pop3::GetMessagesAmount() {
  return 0;
}

bool receiver_pop3::RunStat() {
  if (SendRequest("STAT")) {
	std::string response = ReadResponse();
	return response.find("+OK") != std::string::npos;
  }

  return false;
}

bool receiver_pop3::RunList(uint64_t message_index) {
  std::string command;
  if (message_index) {
	command = fmt::format("LIST {}", message_index);
  } else {
	command = "LIST";
  }

  if (SendRequest(command)) {
	std::string response = ReadResponse();
	bool result = response.find("+OK") != std::string::npos;
	if (result && !message_index) {
	  (void)ReadResponse();
	}
	return result;
  }

  return false;
}

bool receiver_pop3::RunTop(uint64_t message_index, uint64_t rows_amount) {
  std::string command = fmt::format("TOP {} {}", message_index, rows_amount);
  if (SendRequest(command)) {
	std::string response = ReadResponse();
	bool result = response.find("+OK") != std::string::npos;
	if (result) {
	  (void)ReadResponse();
	}

	return result;
  }

  return false;
}

bool receiver_pop3::RunRetrieve(uint64_t message_index, std::string& message) {
  std::string command = fmt::format("RETR {}", message_index);
  if (SendRequest(command)) {
	std::string response = ReadResponse();
	bool result = response.find("+OK") != std::string::npos;
	if (result) {
	  int octets = 0x3200000; // 50MB
	  try {
		auto space_pos = response.find(' ');
		auto space_pos_next = response.find(' ', space_pos + 1);
		octets = std::stoi(response.substr(space_pos, space_pos_next));
	  } catch (std::exception& exception) {
		spdlog::error("Error {} occurred on octets size parsing: {}",
					  typeid(exception).name(), exception.what());
	  }

	  spdlog::info("Trying receive {} octets.", octets);
	  message = ReadResponse(octets * 8);
	}

	return result;
  }

  return false;
}

bool receiver_pop3::RunDelete(uint64_t message_index) {
  std::string command = fmt::format("DELE {}", message_index);
  if (SendRequest(command)) {
	std::string response = ReadResponse();
	return response.find("+OK") != std::string::npos;
  }

  return false;
}

bool receiver_pop3::RunApop() {
  if (SendRequest("APOP")) {
	std::string response = ReadResponse();
	return response.find("+OK") != std::string::npos;
  }

  return false;
}

bool receiver_pop3::RunNoop() {
  if (SendRequest("NOOP")) {
	std::string response = ReadResponse();
	return response.find("+OK") != std::string::npos;
  }

  return false;
}

bool receiver_pop3::RunReset() {
  if (SendRequest("RSET")) {
	std::string response = ReadResponse();
	return response.find("+OK") != std::string::npos;
  }

  return false;
}

bool receiver_pop3::RunQuit() {
  if (SendRequest("QUIT")) {
	std::string response = ReadResponse();
	return response.find("+OK") != std::string::npos;
  }

  return false;
}
} // namespace BirdChirp::Core
