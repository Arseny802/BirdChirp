#pragma once

namespace BirdChirp::Configuration {
class ConfigReader {
 public:
  ConfigReader(std::string_view file_name);
  ~ConfigReader(std::string_view file_name);
};
} // namespace BirdChirp::Configuration