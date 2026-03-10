#include "javactl/cli/command_parser.hpp"

namespace javactl
{
    namespace cli
    {
        CommandType CommandParser::parse(int argc, char* argv[])
        {
            if (argc < 2)
            {
                return CommandType::UNKNOWN;
            }

            std::string cmd = argv[1];
            std::vector<std::string> args;
            for (int i = 2; i < argc; i++)
            {
                args.emplace_back(argv[i]);
            }

            std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
            CommandType cmdType = CommandType::UNKNOWN;
            
            if (cmd == "remote-list")
            {
                cmdType = CommandType::REMOTE_LIST;
            }
            else if (cmd == "help")
            {
                cmdType = CommandType::HELP;
            }
            
            if (cmdType != CommandType::UNKNOWN || cmdType != CommandType::HELP)
            {
                CommandExecutor::execute(cmdType, args);
            }
            
            return CommandType::UNKNOWN;
        }
    }
}