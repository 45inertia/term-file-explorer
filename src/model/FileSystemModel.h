#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <filesystem>
#include <vector>

#include "DirEntry.h"

namespace fs = std::filesystem;

// separation of concerns principle
class FileSystemModel {
public:
  std::vector<DirEntry> ListDirectory(const fs::path& dir);
};

#endif // FILESYSTEMMODEL_H