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

            std::string command = argv[1];
            if (command == "remote-list")
            {
                std::string mirrorName = (argc >= 3) ? argv[2] : "";
                return CommandType::REMOTE_LIST;
            }

            return CommandType::UNKNOWN;
        }
    }
}