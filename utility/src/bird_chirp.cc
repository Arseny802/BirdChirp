#include "pch.h"
#include "receiver_pop3.h"
#include <Setup.h>
#include "arguments.h"
#include "strategies/strategy_factory.h"

static constexpr std::string_view kUtilityVersion = "0.0.1";
static constexpr std::string_view kUtilityDescription =
	"BirdChirp utility. Executes commands to POP3 / IMAP / SMTP server.";

BirdChirp::Utility::Arguments ParseArguments(int argc, char **argv);

int main(int argc, char **argv) {
  auto args = ParseArguments(argc, argv);
  BirdChirpLog::GetInstance()->Info("bird_chirp.utility {}: welcome!", kUtilityVersion);

  try {
	auto strategyPtr = BirdChirp::Utility::StrategyFactory::GetStrategy(args.protocol);
	strategyPtr->Initialize(std::move(args.running_setup));
	strategyPtr->RunCommand(std::move(args.command));
  } catch (std::exception &exception) {
	BirdChirpLog::GetInstance()->Erro("Exception occurred on command processing! {}: {}",
									  typeid(exception).name(), exception.what());
	return EXIT_FAILURE;
  } catch (...) {
	BirdChirpLog::GetInstance()->Crit("Unknown exception occurred on command processing!");
	return EXIT_FAILURE;
  }

  BirdChirpLog::GetInstance()->Info("bird_chirp.utility: see you later!");
  return EXIT_SUCCESS;
}

BirdChirp::Utility::Arguments ParseArguments(int argc, char **argv) {
  TCLAP::CmdLine cmd(kUtilityDescription.data(), ' ', kUtilityVersion.data());

  TCLAP::ValueArg<std::string> argument_host(
	  "H",
	  "host",
	  "Host for connection creating",
	  true,
	  std::string(),
	  "string");
  TCLAP::ValueArg<uint16_t> argument_port(
	  "P",
	  "port",
	  "Port for connection creating",
	  false,
	  0,
	  "uint16");
  TCLAP::ValueArg<bool> argument_tls(
	  "t",
	  "tls",
	  "Needs TLS or not",
	  false,
	  false,
	  "bool");
  TCLAP::ValueArg<std::string> argument_user(
	  "u",
	  "user",
	  "Username for authorization",
	  true,
	  std::string(),
	  "string");
  TCLAP::ValueArg<std::string> argument_pass(
	  "p",
	  "pass",
	  "Password for authorization",
	  true,
	  std::string(),
	  "string");

  std::vector<std::string> allowed_protocols_data(
	  BirdChirp::Utility::ProtocolTraits::kAvailableProtocols.begin(),
	  BirdChirp::Utility::ProtocolTraits::kAvailableProtocols.end());
  TCLAP::ValuesConstraint<std::string> allowed_protocols(allowed_protocols_data);
  TCLAP::ValueArg<std::string> argument_protocol(
	  "m",
	  "mode",
	  "Working protocol mode",
	  true,
	  BirdChirp::Utility::ProtocolTraits::kAvailableProtocols[0].data(),
	  &allowed_protocols);
  TCLAP::ValueArg<uint32_t> argument_command(
	  "c",
	  "command",
	  "Password for authorization",
	  true,
	  0,
	  "uint32");

  try {
	cmd.add(argument_protocol);
	cmd.add(argument_host);
	cmd.add(argument_port);
	cmd.add(argument_tls);
	cmd.add(argument_user);
	cmd.add(argument_pass);
	cmd.add(argument_command);
	cmd.parse(argc, argv);
  } catch (TCLAP::ArgException &exception) {
	BirdChirpLog::GetInstance()->Erro("Exception occurred on arguments parsing! {}: {}",
									  typeid(exception).name(), exception.what());
  }

  BirdChirp::Utility::Arguments result;
  try {
	result.protocol = BirdChirp::Utility::ProtocolTraits::ProtocolFromString(
		argument_protocol.getValue());
	result.command = argument_command.getValue();

	result.running_setup.host = argument_host.getValue();
	result.running_setup.login = argument_user.getValue();
	result.running_setup.password = argument_pass.getValue();
	if (argument_port.isSet()) {
	  result.running_setup.port = argument_port.getValue();
	}

	if (argument_tls.isSet()) {
	  result.running_setup.tls_enabled = argument_tls.getValue();
	}
  } catch (std::exception &exception) {
	BirdChirpLog::GetInstance()->Erro("Exception occurred on arguments parsing! {}: {}",
									  typeid(exception).name(), exception.what());
  }
  return result;
}