cmake_minimum_required(VERSION 3.20)

project(term-file-explorer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- FETCH FTXUI ----------------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v7.0.0
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(ftxui)
# --- FETCH FTXUI ----------------------------------------------------------------------------------

set(SOURCES
  src/main.cpp
  src/model/FileSystemModel.h
  src/model/FileSystemModel.cpp
  src/model/DirEntry.h
)

add_executable(term-file-explorer ${SOURCES})
target_include_directories(term-file-explorer PRIVATE src)

target_link_libraries(term-file-explorer PRIVATE
  # umbrella target
  ftxui::ftxui

  # submodules
  #ftxui::component
  #ftxui::dom
  #ftxui::screen
)