#pragma once
#include "base_strategy.h"
#include "../protocols.h"

namespace BirdChirp::Utility {
class StrategyFactory {
 public:
  static BaseStrategyPtr GetStrategy(std::string_view protocol_name);
  static BaseStrategyPtr GetStrategy(Protocols protocol);
};
} // namespace BirdChirp::Utility
