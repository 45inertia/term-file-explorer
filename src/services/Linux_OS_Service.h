#ifdef __linux__

#ifndef LINUX_OS_SERVICE_H
#define LINUX_OS_SERVICE_H

#include <filesystem>

#include "model/CommandResult.h"

class Linux_OS_Service{
public:
  bool OpenFile(std::filesystem::path path);
  CommandResult RunCommand(std::string cmd, std::filesystem::path cwd);
  // virtual destructor
  ~Linux_OS_Service() = default;
};

#endif // LINUX_OS_SERVICE_H

#endif // __linux__