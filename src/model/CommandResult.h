#ifndef COMMANDRESULT_H
#define COMMANDRESULT_H

#include <string>

struct CommandResult{
  int exitCode;
  std::string stdout_output;
  std::string stderr_output;
};

#endif // COMMANDRESULT_H