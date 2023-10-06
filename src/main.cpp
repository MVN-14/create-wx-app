#include "createwxapp.h"
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    std::string appName;

    if (argc >= 2) {
        appName = argv[1];
    }
    else {
        std::cout << "> Enter app name (no whitespace): ";
        std::cin >> appName;
    }

    for (;;) {
        if (std::filesystem::exists("./" + appName)) {
            std::cout << "Directory ./" << appName
                      << " already exists would you like to overwrite existing"
                         "directory (y/n)?\n";
            char choice;
            std::cin >> choice;
            if (std::tolower(choice) == 'y') {
                break;
            }
            std::cout << "Enter app name (no whitespace): ";
            std::cin >> appName;
            break;
        }
    }

    std::string projectPath = "./" + appName;
    std::string srcPath = projectPath + "/src";
    std::string includePath = projectPath + "/include";

    for (auto &path : {projectPath, srcPath, includePath}) {
        if (!MkDir(path)) {
            std::cerr << "> Couldn't create directory \"" << path << "\n> aborting.\n";
            return -1;
        }
    }

    std::cout << "Generating " << projectPath << "/CMakeLists.txt\n";

    GenerateCMAKEFile(projectPath, appName);
    GenerateHeaderFiles(projectPath);

    return 0;
}
