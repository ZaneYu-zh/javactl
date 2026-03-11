#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include <string>
#include <vector>

namespace javactl::cli {
    enum class CommandType;

    class CommandExecutor {
    public:
        static void execute(CommandType cmdType, const std::vector<std::string> &args);

    private:
        static void validateArgsCount(CommandType cmdType, size_t expectedMin, size_t actual);
    };
}

#endif
