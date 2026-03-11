#ifndef REMOTE_LIST_COMMAND_H
#define REMOTE_LIST_COMMAND_H

#include <string>
#include <vector>

namespace javactl::cli::commands {
    class RemoteListCommand {
    public:
        static void execute(const std::string &mirrorName = "");

    private:
        void printVersionList(const std::string &mirrorName, const std::vector<std::string> &versions);
    };
}

#endif
