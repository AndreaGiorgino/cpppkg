#include <iostream>
#include <string>

auto main(int argc, char** argv) -> int {
    if (argc == 1) {
        // TODO: print help message
        return 0;
    }

    std::size_t argIndex {1};

    // handle options
    for (; argIndex <= argc; argIndex++) {
        const std::string arg {*(argv + argIndex)};

        if (arg.empty())
            continue;
        else if (arg[0] != '-')
            break;
        else if (arg == "-v" || arg == "--version") {
            // TODO: print version message
            return 0;
        } else if (arg == "-h" || arg == "--help") {
            // TODO: print help message
            return 0;
        } else {
            std::cerr << "Unknown option '" << arg << "'\n\n";
            // TODO: print tip message
            return 2;
        }
    }

    // handle commands
    const std::string command {*(argv + argIndex)};

    if (command == "i" || command == "install") {
        // TODO: handle install command
    } else if (command == "d" || command == "delete") {
        // TODO: handle delete command
    } else if (command == "p" || command == "patch") {
        // TODO: handle patch command
    } else if (command == "l" || command == "list") {
        // TODO: handle list command
    } else {
        std::cerr << "Unknown command '" << command << "'\n\n";
        // TODO: print tip message
        return 2;
    }

    return 0;
}
