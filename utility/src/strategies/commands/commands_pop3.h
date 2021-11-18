#pragma once

namespace BirdChirp::Utility {
enum class CommandsPop3 : uint32_t {
  None = 0,
  Stat = 1,
  List = 2,
  Top = 4,
  Retr = 8,
  Dele = 16,
  Apop = 32,
  Noop = 64,
  Rset = 128,
};

} // namespace BirdChirp::Utility
