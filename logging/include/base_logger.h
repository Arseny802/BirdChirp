#pragma once
#include "logger_names.h"
#include <memory>
#include <fmt/format.h>

namespace spdlog {
class logger;
}

namespace BirdChirp::Logging {
class base_logger {
  using logger_ptr = std::unique_ptr<spdlog::logger>;
  std::unique_ptr<spdlog::logger> loggerPtr_;
  static constexpr size_t kMaxFileSize = 20 * 1024 * 1024;
  static constexpr int kMaxFilesAmount = 3;

 public:
  explicit base_logger(std::string_view logger_name = logger_names::kDefault);
  ~base_logger();
/*
  void Trac(std::string_view message);
  void Debu(std::string_view message);
  void Info(std::string_view message);
  void Warn(std::string_view message);
  void Erro(std::string_view message);
  void Crit(std::string_view message);
  void Fata(std::string_view message);
*/

  void Trac(fmt::string_view message);
  void Debu(fmt::string_view message);
  void Info(fmt::string_view message);
  void Warn(fmt::string_view message);
  void Erro(fmt::string_view message);
  void Crit(fmt::string_view message);
  void Fata(fmt::string_view message);

  template<typename ...Args>
  void Trac(std::string_view fmt, Args &&...args);
  template<typename ...Args>
  void Debu(std::string_view fmt, Args &&... args);
  template<typename ...Args>
  void Info(std::string_view fmt, Args &&... args);
  template<typename ...Args>
  void Warn(std::string_view fmt, Args &&... args);
  template<typename ...Args>
  void Erro(std::string_view fmt, Args &&... args);
  template<typename ...Args>
  void Crit(std::string_view fmt, Args &&... args);
  template<typename ...Args>
  void Fata(std::string_view fmt, Args &&... args);

 private:
};

#ifdef NDEGUG
template<typename... Args>
void base_logger::Trac(std::string_view fmt, Args &&... args) {
}
template<typename... Args>
void base_logger::Debu(std::string_view fmt, Args &&... args) {
}
#else
template<typename... Args>
void base_logger::Trac(std::string_view fmt, Args &&... args) {
  fmt::memory_buffer buf;
  fmt::format_to(buf, fmt, args...);
  Trac(fmt::to_string_view(buf.data()));
}

template<typename... Args>
void base_logger::Debu(std::string_view fmt, Args &&... args) {
  fmt::memory_buffer buf;
  fmt::format_to(buf, fmt, std::forward<Args...>(args...));
  Debu(fmt::to_string_view(buf.data()));
}
#endif

template<typename... Args>
void base_logger::Info(std::string_view fmt, Args &&... args) {
  fmt::memory_buffer buf;
  fmt::format_to(buf, fmt, args...);
  Info(fmt::to_string_view(buf.data()));
}
template<typename... Args>
void base_logger::Warn(std::string_view fmt, Args &&... args) {
  fmt::memory_buffer buf;
  fmt::format_to(buf, fmt, args...);
  Warn(fmt::to_string_view(buf.data()));
}
template<typename... Args>
void base_logger::Erro(std::string_view fmt, Args &&... args) {
  fmt::memory_buffer buf;
  fmt::format_to(buf, fmt, args...);
  Erro(fmt::to_string_view(buf.data()));
}

template<typename... Args>
void base_logger::Crit(std::string_view fmt, Args &&... args) {
  fmt::memory_buffer buf;
  fmt::format_to(buf, fmt, args...);
  Crit(fmt::to_string_view(buf.data()));
}

template<typename... Args>
void base_logger::Fata(std::string_view fmt, Args &&... args) {
  fmt::memory_buffer buf;
  fmt::format_to(buf, fmt, args...);
  Fata(fmt::to_string_view(buf.data()));
}
} // namespace BirdChirp::Logging