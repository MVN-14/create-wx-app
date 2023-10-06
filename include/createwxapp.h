#ifndef CREATE_WX_APP_H
#define CREATE_WX_APP_H

#include <string>

bool MkDir(std::string const &path);

bool GenerateCMAKEFile(std::string const &projectPath, std::string const &appName);

bool GenerateHeaderFiles(std::string const &projectPath, std::string const &appName = "createWxApp");

#endif
