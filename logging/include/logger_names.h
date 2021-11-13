#pragma once
#include <string_view>

namespace BirdChirp::Logging {
struct logger_names {
  static constexpr std::string_view kDefault = "bird_chirp";
  static constexpr std::string_view kApplication = "app";
  static constexpr std::string_view kClient = "client";
  static constexpr std::string_view kServer = "server";
  static constexpr std::string_view kCore = "core";
  static constexpr std::string_view kUtility = "util";
};
} // namespace BirdChirp::Logging