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

  (void)ReadResponse();
  return true;
}

bool base_mail_receiver::SendRequest(std::string_view request) {
  if (request.size() <= kMaxMessageSizeToLog) {
	spdlog::info("Running command '{}'.", request);
  } else {
	spdlog::info("Running too big command.");
  }
  std::vector<char> request_buffer(request.size() + 2);
  memccpy(request_buffer.data(), request.data(), 0, request.size());
  request_buffer[request.size()] = '\r';
  request_buffer[request.size() + 1] = '\n';

  asio::error_code error_code;
  auto bytes_transferred = asio::write(*socket_, asio::dynamic_buffer(request_buffer), error_code);
  spdlog::debug("Request: {} bytes transferred.", bytes_transferred);

  if (error_code) {
	spdlog::error("Request error {}. Message: {}",
				  error_code.value(), error_code.message());
	return false;
  }

  return bytes_transferred;
}

std::string base_mail_receiver::ReadResponse(size_t max_message_size) const {
  spdlog::debug("Waiting for response, {} bytes awaited.", max_message_size);
  asio::error_code error_code;
  std::vector<char> buffer;

  auto bytes_transferred = asio::read_until(
	  *socket_,
	  asio::dynamic_buffer(buffer, max_message_size),
	  "\r\n",
	  error_code);
  spdlog::debug("Response: {} bytes transferred.", bytes_transferred);

  if (error_code) {
	spdlog::error("Response error {}. Message: {}",
				  error_code.value(), error_code.message());
  }

  if (buffer.size() <= kMaxMessageSizeToLog) {
	spdlog::info("Got response: {}", buffer.data());
  } else {
	spdlog::info("Got too big response response.");
  }
  return buffer.data();
}
} // namespace BirdChirp::Core