#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <string>
#include "javactl/cli/command_parser.hpp"
#include "javactl/cli/commands/remote_list_command.hpp"

namespace javactl
{
    namespace cli
    {
        class CommandExecutor
        {
            public:
            static void execute(CommandType cmdType, const std::vector<std::string>& args);

            private:
            static void validateArgsCount(CommandType cmdType, size_t expectedMin, size_t actual);
        };
    }
}

#endif