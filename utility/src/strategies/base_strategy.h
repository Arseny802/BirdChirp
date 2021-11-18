#pragma once
#include "Setup.h"

namespace BirdChirp::Utility {
class BaseStrategy {
 public:
  BaseStrategy();
  ~BaseStrategy();

  bool Initialize(Core::Setup &&running_setup);
  virtual std::string RunCommand(uint32_t command_code) = 0;

 protected:
  Core::Setup running_setup_;

 private:

};
using BaseStrategyPtr = std::shared_ptr<BaseStrategy>;
} // namespace BirdChirp::Utility
