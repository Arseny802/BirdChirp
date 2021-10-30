#include <asio/connect.hpp>
#include <asio/read.hpp>
#include <utility>
#include <asio/read_until.hpp>
#include "pch.h"
#include "base_mail_receiver.h"

namespace BirdChirp::Core {
base_mail_receiver::base_mail_receiver(setup settings)
	: settings_(std::move(settings)),
	  ssl_context_(asio::ssl::context::tls_client),
	  resolver_(io_context_) {
  socket_ = std::make_unique<ssl_socket>(io_context_, ssl_context_);
}

bool base_mail_receiver::Connect() {
  spdlog::info("Creating connection to '{}:{}'.", settings_.host, settings_.port);
  auto endpoints = resolver_.resolve(settings_.host, std::to_string(settings_.port));
  asio::connect(socket_->next_layer(), endpoints);
  asio::error_code error_code;
  socket_->handshake(asio::ssl::stream_base::client, error_code);
  if (error_code) {
	spdlog::error("Handshake error {}. Message: {}",
				  error_code.value(), error_code.message());
	return false;
  }

  PrintResponse();
  return true;
}

bool base_mail_receiver::Authorize() {
  return false;
}

int base_mail_receiver::GetMessagesAmount() {
  return 0;
}

bool base_mail_receiver::SendRequest(std::string_view request) {
  spdlog::info("Running command '{}'.", request);
  std::ostream request_stream(&request_buffer_);
  request_stream << request << "\r\n";
  asio::error_code error_code;
  auto bytes_transferred = asio::write(*socket_, request_buffer_, error_code);
  spdlog::info("Request: {} bytes transferred.", bytes_transferred);

  if (error_code) {
	spdlog::error("Request error {}. Message: {}",
				  error_code.value(), error_code.message());
	PrintResponse();
	return false;
  }

  PrintResponse();
  return bytes_transferred;
}

void base_mail_receiver::PrintResponse() {
  asio::error_code error_code;
  std::vector<char> buffer;

  auto bytes_transferred = asio::read_until(
	  *socket_,
	  asio::dynamic_buffer(buffer, 1024),
	  "\n",
	  error_code);
  spdlog::info("Response: {} bytes transferred.", bytes_transferred);

  if (error_code) {
	spdlog::error("Response error {}. Message: {}",
				  error_code.value(), error_code.message());
  }

  std::stringstream response_string;
  response_string << std::istream(&response_buffer_).rdbuf();
  spdlog::info("Got response: {}", buffer.data());
}
} // namespace BirdChirp::Core