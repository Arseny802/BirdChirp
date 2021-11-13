#pragma once
#include "base_logger.h"

namespace BirdChirp::Logging {
class core_logger : public base_logger {
 public:
  core_logger() : base_logger(logger_names::kCore) {

  }
};
} // namespace BirdChirp::Logging
