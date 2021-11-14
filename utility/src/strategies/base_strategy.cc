#include "../pch.h"
#include "base_strategy.h"

namespace BirdChirp::Utility {
BaseStrategy::BaseStrategy() {

}
BaseStrategy::~BaseStrategy() = default;

bool BaseStrategy::Initialize(Core::Setup &&running_setup) {
  running_setup_ = running_setup;
  return true;
}

std::string BaseStrategy::RunCommand(std::string &&command) {
  ParseCommand(std::move(command));
  return RunCommand(0);
}

void BaseStrategy::ParseCommand(std::string &&command) {

}
} // namespace BirdChirp::Utility
