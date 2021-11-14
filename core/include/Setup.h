#pragma once
#include <string>
#include <optional>

namespace BirdChirp::Core {
struct Setup {
  std::string login;
  std::string password;
  std::string host;
  std::optional<uint16_t> port;
  std::optional<bool> tls_enabled;
};
} // namespace BirdChirp::Core
