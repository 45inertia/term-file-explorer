#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include <filesystem>

#include "model/DirEntry.h"
#include "model/FileSystemModel.h"

namespace fs = std::filesystem;



int main() {
  fs::path root = fs::absolute("/");

  FileSystemModel model;
  std::vector<DirEntry> list = model.ListDirectory(root);

  std::cout << root << std::endl;
  
  for(DirEntry& item : list) {
    std::cout << item.name_ << '\n' << item.is_directory_ << '\n' << item.size_ << std::endl;
  }

  list = model.ListDirectory(fs::current_path());

  for(DirEntry& item : list) {
    std::cout << item.name_ << '\n' << item.is_directory_ << '\n' << item.size_ << std::endl;
  }

  
  return 0;
}