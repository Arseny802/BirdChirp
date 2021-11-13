#include "include/base_logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace BirdChirp::Logging {
base_logger::base_logger(std::string_view logger_name) {

  auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
	  fmt::format("logs/{}", logger_name.data()), kMaxFileSize, kMaxFilesAmount);
  file_sink->set_level(spdlog::level::trace);

#ifndef NDEBUG
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::warn);
  console_sink->set_pattern("[%H:%M:%S:%F] [PID %5!P] [T %5!t] [%4!l] %v");

  spdlog::logger logger("bird_chirp", {console_sink, file_sink});
  std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
  loggerPtr_ = std::make_unique<spdlog::logger>(logger_name.data(), sinks.begin(), sinks.end());
#else
  spdlog::logger logger("multi_sink", {file_sink});
  loggerPtr_ = std::make_unique<spdlog::logger>("multi_sink", {file_sink});
#endif

  spdlog::flush_every(std::chrono::seconds(15));
  spdlog::flush_on(spdlog::level::info);
}

base_logger::~base_logger() = default;
/*
#ifdef NDEGUG
void base_logger::Trac(std::string_view message) {
}
void base_logger::Debu(std::string_view message) {
}
#else
void base_logger::Trac(std::string_view message) {
  loggerPtr_->trace(message);
}
void base_logger::Debu(std::string_view message) {
  loggerPtr_->debug(message);
}
#endif

void base_logger::Info(std::string_view message) {
  loggerPtr_->info(message);
}
void base_logger::Warn(std::string_view message) {
  loggerPtr_->warn(message);
}
void base_logger::Erro(std::string_view message) {
  loggerPtr_->error(message);
}
void base_logger::Crit(std::string_view message) {
  loggerPtr_->critical(message);
}
void base_logger::Fata(std::string_view message) {
  loggerPtr_->critical(message);
}
*/

#ifdef NDEGUG
void base_logger::Trac(fmt::string_view message) {
}
void base_logger::Debu(fmt::string_view message) {
}
#else
void base_logger::Trac(fmt::string_view message) {
  loggerPtr_->trace(message);
}
void base_logger::Debu(fmt::string_view message) {
  loggerPtr_->debug(message);
}
#endif

void base_logger::Info(fmt::string_view message) {
  loggerPtr_->info(message);
}
void base_logger::Warn(fmt::string_view message) {
  loggerPtr_->critical(message);
}
void base_logger::Erro(fmt::string_view message) {
  loggerPtr_->error(message);
}
void base_logger::Crit(fmt::string_view message) {
  loggerPtr_->critical(message);
}
void base_logger::Fata(fmt::string_view message) {
  loggerPtr_->critical(message);
}
} // namespace BirdChirp::Logging
