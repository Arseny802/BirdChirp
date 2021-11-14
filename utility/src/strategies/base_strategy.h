#pragma once
#include "Setup.h"

namespace BirdChirp::Utility {
class BaseStrategy {
 public:
  BaseStrategy();
  ~BaseStrategy();

  bool Initialize(Core::Setup &&running_setup);
  std::string RunCommand(std::string &&command);

 protected:
  Core::Setup running_setup_;
 private:
  void ParseCommand(std::string &&command);

  virtual std::string RunCommand(uint32_t command_code) = 0;

};
using BaseStrategyPtr = std::shared_ptr<BaseStrategy>;
} // namespace BirdChirp::Utility
