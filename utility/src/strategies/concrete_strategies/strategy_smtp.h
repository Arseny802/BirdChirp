#pragma once
#include "../base_strategy.h"

namespace BirdChirp::Utility {
class StrategySmtp : public BaseStrategy {
 public:
  std::string RunCommand(uint32_t command_code) override;
};
} // namespace BirdChirp::Utility
