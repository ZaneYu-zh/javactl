#ifndef REMOTE_LIST_COMMAND_H
#define REMOTE_LIST_COMMAND_H

#include <string>
#include <vector>

namespace javactl
{
    namespace cli
    {
        namespace commands
        {
            class RemoteListCommand
            {
                public:
                void execute(const std::string& mirrorName = "");

                private:
                void printVersionList(const std::string& mirrorName, const std::vector<std::string>& versions);
            };
        }
    }
}

#endif