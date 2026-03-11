#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

namespace javactl::cli {
    enum class CommandType {
        UNKNOWN,
        REMOTE_LIST,
        HELP
    };

    class CommandParser {
    public:
        static CommandType parse(int argc, char *argv[]);
    };
}

#endif
