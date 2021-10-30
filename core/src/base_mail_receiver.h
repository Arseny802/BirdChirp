#pragma once
#include <asio/io_context.hpp>
#include <asio/ssl/context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/streambuf.hpp>
#include <asio/ssl/stream.hpp>
#include "../include/setup.h"

namespace BirdChirp::Core {
class base_mail_receiver {
  using ssl_socket = asio::ssl::stream<asio::ip::tcp::socket>;
 public:
  explicit base_mail_receiver(setup settings);

  bool Connect();
  virtual bool Authorize();
  virtual int GetMessagesAmount();
  void PrintResponse();

 protected:
  bool SendRequest(std::string_view request);

  static constexpr uint16_t kDefaultPort_Pop3 = 110;
  static constexpr uint16_t kDefaultPort_Imap = 111;
  static constexpr uint16_t kDefaultPort_Smtp = 25;

  setup settings_;

 private:
  asio::io_context io_context_;
  asio::ssl::context ssl_context_;
  asio::ip::tcp::resolver resolver_;
  std::unique_ptr<ssl_socket> socket_;
  asio::streambuf request_buffer_;
  asio::streambuf response_buffer_;
};
} // namespace BirdChirp::Core
