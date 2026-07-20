# Research <!-- omit from toc -->

This markdown document tracks questions that I have about the implementation and design of this
project.

## Contents <!-- omit from toc -->

- [Reading Directory Contents Cross Platform](#reading-directory-contents-cross-platform)
- [Opening documents and running commands cross platform](#opening-documents-and-running-commands-cross-platform)
- [Architecture Ideas](#architecture-ideas)
- [Considering Running Commands (Block UI or run async)](#considering-running-commands-block-ui-or-run-async)
- [Breaking up the code (AI recommended)](#breaking-up-the-code-ai-recommended)
- [Error Handling](#error-handling)

## Reading Directory Contents Cross Platform

`std::filesystem` (C++17) handles directory listing identically on Windows and Linux. This works
because `std::filesystem` is designed as an OS abstraction layer.

**A few things worth noting**

`directory_iterator` can throw permissions erros and broken symlinks. Wrap it or use the non
throwing overload that takes `std::error_code&` if you don't want a bad directory to crash the app.

Path separators are handled automatically `fs::path` normalizes `\` vs `/`.

`fs::current_path()` gets starting pwd

## Opening documents and running commands cross platform

This is where "cross-platform" breaks down as there is no unified standard library facility.

Realistically we can implement a small abstraction layer like an `OsCommands` interface with
`OpenFile(path)` and `RunCommand(cmd)` with two implementations selected via `#ifdef _WIN32` / 
`#ifdef __linux__` at compile time.

Or two separate `.cpp` files only one of which gets compiled per platform via CMake `if(WIN32)` and
`if(UNIX)` conditionals

## Architecture Ideas

The model in **MVVM** could be a thin wrapper around filesystem access that presents it as clean,
structured data to the rest of the app

Something like:
```cpp
struct DirEntry {
  std::string name;
  bool is_directory;
  uintmax_t size;
};

class FileSystemModel {
  public:
    std::vector<DirEntry> ListDirectory(const fs::path& dir);
    bool OpenFile(const fs::path& file);
    bool RunCommand(const std::string& cmd, const fs::path& cwd);
};
```

The ViewModel then holds UI relevant state and exposes intent driven operations, not raw data 
access.

## Considering Running Commands (Block UI or run async)

The FTXUI event loop is single threaded and will freeze if a command is long running.

Eventually a solution needed is to spawn the command on a separate thread and use FTXUI's 
`PostEvent`/screen-refresh-from-another-thread mechanism to update the UI once it completes.

## Breaking up the code (AI recommended)

During the initial design process AI has been used as a consultant for architecture and project
structure. 

```
src/
  model/
    file_system_model.hpp / .cpp
  services/
    os_service.hpp              (abstract interface)
    windows_os_service.cpp      (only compiled on WIN32)
    linux_os_service.cpp        (only compiled on UNIX)
  viewmodel/
    file_explorer_viewmodel.hpp / .cpp
  ui/
    components/
      menu_panel.hpp / .cpp     (the directory listing menu)
      path_bar.hpp / .cpp       (breadcrumb / current path display)
      command_input.hpp / .cpp  (the command-entry box)
    tree_main.hpp / .cpp        (composes the above into the full screen)
  main.cpp
```

Need to think about whether the ViewModel exposes mutable references like `SelectedIndexRef()` for
FTXUI's pointer binding style or whether `CatchEvent` callback driven updates are used instead.

## Error Handling

What happens when `list_directory()` hits a permission denied folder? The main thing to decide is
does the ViewModel store an "error message" field that the UI can display (same pattern as
`last_command_result`)

There should be an error message stored with a title and description.