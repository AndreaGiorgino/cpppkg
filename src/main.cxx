#include <help.hxx>
#include <iostream>
#include <string>
#include <version.hxx>

auto main(int argc, char** argv) -> int {
    if (argc == 1) {
        std::cout << HELP_MESSAGE << std::endl;
        return 0;
    }

    int argIndex {1};

    // global options
    bool force {};

    // handle options
    for (; argIndex < argc; argIndex++) {
        const std::string arg {*(argv + argIndex)};

        if (arg.empty())
            continue;
        else if (arg[0] != '-')
            break;
        else if (arg == "-v" || arg == "--version") {
            std::cout << VERSION_MESSAGE << std::endl;
            return 0;
        } else if (arg == "-h" || arg == "--help") {
            std::cout << HELP_MESSAGE << std::endl;
            return 0;
        } else if (arg == "--force")
            force = true;
        else {
            std::cerr << "Unknown option '" << arg << "'\n\n";
            std::cout << TIP_MESSAGE << std::endl;
            return 2;
        }
    }

    if (argIndex == argc) {
        std::cerr << "Missing command\n\n";
        std::cout << TIP_MESSAGE << std::endl;
        return 2;
    }

    // handle commands
    const std::string command {*(argv + argIndex)};

    if (command == "i" || command == "install") {
        // TODO: handle install command
    } else if (command == "l" || command == "list") {
        // TODO: handle list command
    } else {
        std::cerr << "Unknown command '" << command << "'\n\n";
        std::cout << TIP_MESSAGE << std::endl;
        return 2;
    }

    return 0;
}
