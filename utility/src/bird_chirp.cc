#include <iostream>
#include "../../client/include/receiver_pop3.h"
#include <setup.h>
#include <spdlog/spdlog.h>

int main() {
  spdlog::info("bird_chirp.utility: welcome!");
  BirdChirp::Core::setup settings;
  settings.host = "pop3.mail.ru";
  settings.port = 995;

  std::cout << "Enter login: ";
  std::cin >> settings.login;
  std::cout << "Enter password: ";
  std::cin >> settings.password;

  BirdChirp::Core::receiver_pop3 receiver_pop3(settings);
  if (receiver_pop3.Connect() && receiver_pop3.Authorize()) {
	receiver_pop3.RunStat();
	//receiver_pop3.RunTop(1);
	std::string first_message;
	receiver_pop3.RunRetrieve(1, first_message);
	receiver_pop3.RunList();
	receiver_pop3.RunQuit();
  }

  spdlog::info("bird_chirp.utility: see you later!");
  return EXIT_SUCCESS;
}
