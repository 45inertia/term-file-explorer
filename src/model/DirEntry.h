#ifndef DIRENTRY_H
#define DIRENTRY_H

#include <string>
#include <cstdint>

struct DirEntry {
  std::string name_;
  bool is_directory_;
  uintmax_t size;   // this is an unsigned integer type from <cstdint> guaranteed to be at least
                    // as wide as any other unsigned integer type. This is what
                    // std::filesystem::directory_entry::file_size() actually returns.
};

#endif // DIRENTRY_H