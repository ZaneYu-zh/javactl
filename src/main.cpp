#include <iostream>
#include <string>
#include <curl/curl.h>
#include "javactl/cli/command_parser.hpp"

void help() {
    std::cout << "Usage" << std::endl;
    std::cout << std::endl;
    std::cout << "  javactl <command> [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "A cross-platform Java version management tool to install, switch, uninstall, and list Java versions"
            << std::endl;
    std::cout << "with configurable mirror sources for fast and reliable downloads of remote Java distributions." <<
            std::endl;
    std::cout << std::endl;
    std::cout << "Commands" << std::endl;
    std::cout << "  remote-list [mirror]    List available Java versions from a specified (or default) mirror source" <<
            std::endl;
}

int main(const int argc, char *argv[]) {
    if (const CURLcode curlInitRes = curl_global_init(CURL_GLOBAL_ALL); curlInitRes != CURLE_OK) {
        std::cerr << "JavaCtl Error: libcurl init failed, " << curl_easy_strerror(curlInitRes) << std::endl;
        return 1;
    }

    int exitCode = 0;
    try {
        if (argc == 1) {
            help();
            return 0;
        }

        switch (javactl::cli::CommandType cmdType = javactl::cli::CommandParser::parse(argc, argv)) {
            case javactl::cli::CommandType::UNKNOWN:
                std::cerr << "JavaCtl Error: unknown command " << argv[1] << std::endl;
                std::cerr << "JavaCtl Error: \'Run javactl help\' for all supported commands" << std::endl;
                exitCode = 1;
                break;

            case javactl::cli::CommandType::HELP:
                help();
                break;
            default: ;
        }
    } catch (...) {
        std::cerr << "Unknown Error: please check command arguments or network." << std::endl;
        exitCode = 1;
    }

    curl_global_cleanup();

    return exitCode;
}
