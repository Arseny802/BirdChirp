#pragma once
#include "base_logger.h"

namespace BirdChirp::Logging {
class utility_logger : public base_logger {
 public:
  utility_logger() : base_logger(logger_names::kUtility) {

  }
};
} // namespace BirdChirp::Logging
