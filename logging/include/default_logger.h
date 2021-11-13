#pragma once
#include "base_logger.h"
#include "singleton.h"

namespace BirdChirp::Logging {
class default_logger : public base_logger {
 public:
  default_logger() : base_logger(logger_names::kDefault) {
  }
};
} // namespace BirdChirp::Logging

using BirdChirpLog = BirdChirp::Tools::singleton<BirdChirp::Logging::default_logger>;
