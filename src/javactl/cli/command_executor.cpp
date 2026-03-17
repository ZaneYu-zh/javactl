#include "javactl/cli/command_executor.hpp"
#include "javactl/cli/command_parser.hpp"
#include "javactl/cli/commands/remote_list_command.hpp"

namespace javactl::cli {
    void CommandExecutor::execute(const CommandType cmdType, const std::vector<std::string> &args) {
        switch (cmdType) {
            case CommandType::REMOTE_LIST: {
                validateArgsCount(cmdType, 0, args.size());
                const std::string mirror = args.empty() ? "" : args[0];
                commands::RemoteListCommand::execute(mirror);
                break;
            }


            default:
                break;
        }
    }

    void CommandExecutor::validateArgsCount(const CommandType cmdType, size_t expectedMin, const size_t actual) {
        if (actual < expectedMin) {
            std::string cmdName;
            switch (cmdType) {
                case CommandType::REMOTE_LIST: cmdName = "remote-list";
                    break;
                default:
                    break;
            }
            exit(1);
        }
    }
}