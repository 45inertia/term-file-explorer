#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <filesystem>
#include <vector>

#include "DirEntry.h"

// separation of concerns principle
class FileSystemModel {
public:
  std::vector<DirEntry> ListDirectory(const std::filesystem::path& dir);
};

#endif // FILESYSTEMMODEL_H