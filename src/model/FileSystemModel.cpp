#include "FileSystemModel.h"

#include "DirEntry.h"

#include <vector>
#include <filesystem>

// namespace alias here instead of the header so it doesn't leak
namespace fs = std::filesystem;
 
std::vector<DirEntry> FileSystemModel::ListDirectory(const fs::path& dir) {
  std::vector<DirEntry> list_;
  if(!fs::is_directory(dir)) {
    return list_;
  }
  for(auto &item : fs::directory_iterator(dir)) {
    try {
      list_.push_back(DirEntry{
        item.path().filename().string(),
        item.is_directory(),
        item.is_directory() ? 0 : item.file_size()
      });
    } catch (const fs::filesystem_error&) {
      // skip entries that can't be read
      continue;
    }
  }
  return list_;
}
