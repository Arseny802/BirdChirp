#pragma once
#include "base_logger.h"

namespace BirdChirp::Logging {
class client_logger : public base_logger {
 public:
  client_logger() : base_logger(logger_names::kClient) {

  }
};
} // namespace BirdChirp::Logging
