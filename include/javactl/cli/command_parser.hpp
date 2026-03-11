#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>
#include <algorithm>

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