#pragma once
#include <asio/io_context.hpp>
#include <asio/ssl/context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/streambuf.hpp>
#include <asio/ssl/stream.hpp>
#include "../../include/Setup.h"

namespace BirdChirp::Core {
class base_mail_receiver {
  using ssl_socket = asio::ssl::stream<asio::ip::tcp::socket>;
 public:
  explicit base_mail_receiver(Setup settings);

  bool Connect();
  virtual bool Authorize() = 0;
  virtual int GetMessagesAmount() = 0;

  [[nodiscard]] std::string ReadResponse(size_t max_message_size = kDefaultMaxMessageSize) const;

 protected:
  bool SendRequest(std::string_view request);

  static constexpr size_t kDefaultMaxMessageSize = std::numeric_limits<size_t>::max();
  static constexpr size_t kMaxMessageSizeToLog = 1024;

  Setup settings_;

 private:
  asio::io_context io_context_;
  asio::ssl::context ssl_context_;
  asio::ip::tcp::resolver resolver_;
  std::unique_ptr<ssl_socket> socket_;
};
} // namespace BirdChirp::Core
