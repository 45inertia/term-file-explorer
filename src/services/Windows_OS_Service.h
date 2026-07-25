#ifdef _WIN32

#ifndef WINDOWS_OS_SERVICE_H
#define WINDOWS_OS_SERVICE_H

#include <filesystem>

#include "model/CommandResult.h"

class Windows_OS_Service{
public:
  bool OpenFile(std::filesystem::path path);
  CommandResult RunCommand(std::string cmd, std::filesystem::path cwd);
  
  ~Windows_OS_Service() = default;
};


#endif // WINDOWS_OS_SERVICE_H

#endif // _WIN32