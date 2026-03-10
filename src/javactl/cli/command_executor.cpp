#include "javactl/cli/command_executor.hpp"

namespace javactl
{
    namespace cli
    {
        void CommandExecutor::execute(CommandType cmdType, const std::vector<std::string>& args)
        {
            switch (cmdType)
            {
            case CommandType::REMOTE_LIST:
            {
                validateArgsCount(cmdType, 0, args.size());
                commands::RemoteListCommand cmd;
                std::string mirror = args.empty() ? "" : args[0];
                cmd.execute(mirror);
                break;
            }
                
            
            default:
                break;
            }
        }

        void CommandExecutor::validateArgsCount(CommandType cmdType, size_t expectedMin, size_t actual)
        {
            if (actual < expectedMin)
            {
                std::string cmdName;
                switch (cmdType)
                {
                case CommandType::REMOTE_LIST: cmdName = "remote-list"; break;
                default:
                    break;
                }
                exit(1);
            }
        }
    }
}