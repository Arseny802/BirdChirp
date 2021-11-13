#pragma once
#include "base_logger.h"

namespace BirdChirp::Logging {
class server_logger : public base_logger {
  server_logger() : base_logger(logger_names::kServer) {

  }
};
} // namespace BirdChirp::Logging
