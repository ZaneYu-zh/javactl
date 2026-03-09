#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>

namespace javactl
{
    namespace cli
    {
        enum class CommandType
        {
            UNKNOWN,
            REMORE_LIST
        };

        class CommandParser
        {
            public:
            CommandType parse(int argc, char* agrv[]);
        };
    }
}

#endif