#pragma once

namespace BirdChirp::Utility {
enum class Protocols {
  Undefined = 0,
  Pop3 = 1,
  Imap = 2,
  Smtp = 3
};

struct ProtocolTraits {
  static constexpr std::array<std::string_view, 3> kAvailableProtocols {
	"pop3", "imap", "smtp"
  };

  static Protocols ProtocolFromString(const std::string_view type) {
	switch (type[0]) {
	  case kAvailableProtocols[0][0]: return Protocols::Pop3;
	  case kAvailableProtocols[1][0]: return Protocols::Imap;
	  case kAvailableProtocols[2][0]: return Protocols::Smtp;
	  default: return Protocols::Undefined;
	}
  }

  static std::string ProtocolToString(Protocols protocol) {
	switch (protocol) {
	  case Protocols::Pop3: return kAvailableProtocols[0].data();
	  case Protocols::Imap: return kAvailableProtocols[1].data();
	  case Protocols::Smtp: return kAvailableProtocols[2].data();
	  case Protocols::Undefined:
	  default: return "undefined";
	}
  }
};
} // namespace BirdChirp::Utility
