#pragma once
#include <asio/ip/tcp.hpp>
#include <asio/ssl/stream.hpp>
#include <asio/streambuf.hpp>
#include "../src/base_mail_receiver.h"

namespace BirdChirp::Core {
class receiver_pop3 : public base_mail_receiver {
 public:
  explicit receiver_pop3(const setup &settings);
  ~receiver_pop3();

  bool Authorize() override;
  int GetMessagesAmount() override;

  bool RunStat();
  bool RunList(uint64_t message_index = 0);
  bool RunTop(uint64_t message_index, uint64_t rows_amount = 3);
  bool RunRetrieve(uint64_t message_index);
  bool RunDelete(uint64_t message_index);
  bool RunApop();
  bool RunNoop();
  bool RunReset();
  bool RunQuit();

 protected:
  bool RunUser();
  bool RunPass();
};
} // namespace BirdChirp::Core
