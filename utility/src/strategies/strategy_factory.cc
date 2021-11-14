#include "../pch.h"
#include "strategy_factory.h"
#include "concrete_strategies/strategy_imap.h"
#include "concrete_strategies/strategy_pop3.h"
#include "concrete_strategies/strategy_smtp.h"

namespace BirdChirp::Utility {
BaseStrategyPtr StrategyFactory::GetStrategy(std::string_view protocol_name) {
  return GetStrategy(ProtocolTraits::ProtocolFromString(protocol_name));
}
BaseStrategyPtr StrategyFactory::GetStrategy(Protocols protocol) {
  switch (protocol) {
	case Protocols::Pop3: return std::make_shared<StrategyPop3>();
	case Protocols::Imap: return std::make_shared<StrategyImap>();
	case Protocols::Smtp: return std::make_shared<StrategySmtp>();
	default: return nullptr;
  }
}
}