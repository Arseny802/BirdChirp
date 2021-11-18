#pragma once
#include "protocols.h"

namespace BirdChirp::Utility {
struct Arguments {
  Protocols protocol;
  uint32_t command;
  BirdChirp::Core::Setup running_setup;
};
} // namespace BirdChirp::Utility
