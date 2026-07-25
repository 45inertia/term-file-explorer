#ifndef OS_SERVICE_H
#define OS_SERVICE_H

#include <filesystem>

#include "model/CommandResult.h"

class OS_Service{
public:
  virtual bool OpenFile(std::filesystem::path path) = 0;
  virtual CommandResult RunCommand(std::string cmd, std::filesystem::path cwd) = 0;
  // virtual destructor
  virtual ~OS_Service() = default;
};

#endif // OS_SERVICE_H