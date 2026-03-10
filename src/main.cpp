#include <iostream>
#include <string>
#include <curl/curl.h>
#include "javactl/cli/command_parser.hpp"
#include "javactl/os/os_detector.hpp"

void help()
{
    std::cout << "Usage" << std::endl;
    std::cout << std::endl;
    std::cout << "  javactl <command> [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "A cross-platform Java version management tool to install, switch, uninstall, and list Java versions" << std::endl;
    std::cout << "with configurable mirror sources for fast and reliable downloads of remote Java distributions." << std::endl;
    std::cout << std::endl;
    std::cout << "Commands" << std::endl;
    std::cout << "  remote-list [mirror]    List available Java versions from a specified (or default) mirror source" << std::endl;
}

int main(int argc, char* argv[])
{
    CURLcode curlInitRes = curl_global_init(CURL_GLOBAL_ALL);
    if (curlInitRes != CURLE_OK)
    {
        std::cerr << "JavaCtl Error: libcurl init failed, " << curl_easy_strerror(curlInitRes) << std::endl;
        return 1;
    }

    int exitCode = 0;
    try
    {
        if (argc == 1)
        {
            help();
            return 0;
        }

        javactl::cli::CommandParser parser;
        javactl::cli::CommandType cmdType = parser.parse(argc, argv);

        switch (cmdType)
        {
            case javactl::cli::CommandType::UNKNOWN:
                std::cerr << "JavaCtl Error: unknown command " << argv[1] << std::endl;
                std::cerr << "JavaCtl Error: \'Run javactl help\' for all supported commands" << std::endl;
                exitCode = 1;
                break;

            case javactl::cli::CommandType::HELP:
                break;
        }
    }
    catch (...) 
    {
        std::cerr << "Unknown Error: please check command arguments or network." << std::endl;
        exitCode = 1;
    }

    curl_global_cleanup();

    return exitCode;
}