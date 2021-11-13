#pragma once
#include "base_logger.h"

namespace BirdChirp::Logging {
class application_logger : public base_logger {
 public:
  application_logger() : base_logger(logger_names::kApplication) {

  }
};
} // namespace BirdChirp::Logging
