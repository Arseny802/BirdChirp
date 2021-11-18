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
} // namespace BirdChirp::Utility
