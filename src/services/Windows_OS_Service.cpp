#include "Windows_OS_Service.h"

#include "model/CommandResult.h"

#include <filesystem>
#include <shellapi.h>


bool Windows_OS_Service::OpenFile(std::filesystem::path path) {
  ShellExecute(NULL, "open", path, NULL, NULL, 1);
}
  
CommandResult Windows_OS_Service::RunCommand(std::string cmd, std::filesystem::path cwd) {

}