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
        while (true) {
            std::cout << "> Enter app name (no whitespace): ";
            std::cin >> appName;

            if (std::filesystem::exists("./" + appName)) {
                std::cout << "> Directory ./" << appName
                          << " already exists would you like to overwrite existing "
                             "directory (y/N)?\n> ";
                char choice;
                std::cin >> choice;
                if (std::tolower(choice) == 'y') {
                    std::filesystem::remove_all("./" + appName);
                    break;
                }
            }
            else {
                break;
            }
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

    std::cout << "> Generating " << projectPath << "/CMakeLists.txt\n";
    if (!GenerateCMAKEFile(projectPath, appName)) {
        std::cerr << "Error generating CMakeLists.txt...\naborting.\n";
    }

    std::cout << "> Generating  header files...\n";
    if (!GenerateHeaderFiles(projectPath, appName)) {
        std::cerr << "> Error generating header files...\naborting.\n";
    }

    std::cout << "> Generating source files...\n";
    if (!GenerateSourceFiles(projectPath, appName)) {
        std::cerr << "> Error generating source files...\naborting.\n";
    }

    return 0;
}
