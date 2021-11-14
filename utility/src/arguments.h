#pragma once
#include "protocols.h"

namespace BirdChirp::Utility {
struct Arguments {
  Protocols protocol;
  std::string command;
  BirdChirp::Core::Setup running_setup;
};
} // namespace BirdChirp::Utility
