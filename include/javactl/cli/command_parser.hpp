#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>
#include <algorithm>
#include <javactl/cli/command_executor.hpp>

namespace javactl
{
    namespace cli
    {
        enum class CommandType
        {
            UNKNOWN,
            REMOTE_LIST,
            HELP
        };

        class CommandParser
        {
            public:
            CommandType parse(int argc, char* argv[]);
        };
    }
}

#endif