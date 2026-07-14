# Architecture <!-- omit from toc -->

## Contents <!-- omit from toc -->

- [Class Diagram](#class-diagram)
- [Component/Architecture Diagram](#componentarchitecture-diagram)
- [Sequence Diagram](#sequence-diagram)
  - [Navigating into a Directory](#navigating-into-a-directory)
  - [Running a Shell Command](#running-a-shell-command)
- [State Diagram](#state-diagram)

## Class Diagram
**Class Diagram Version 1.0**
```mermaid
---
title: term-file-explorer
---
classDiagram
    class main{
        +main() int
    }
    main --> file_explorer_viewmodel
    main --> windows_os_service
    main --> linux_os_service
    main --> tree_main
    class command_result {
      + int exit_code
      + string stdout_output
      + string stderr_output 
    }
    class dir_entry{
        + string name
        + bool is_directory
        + uintmax_t size 
    }
    class file_system_model{
        + list_directory(path) vector~dir_entry~
    }

    class file_explorer_viewmodel{
        - fs::path current_path_
        - file_system_model fsm_
        - vector~dir_entry~ entries_
        - vector~string~ display_names_
        - int selected_
        - unique_ptr~os_service~ os_
        - command_result last_command_result_



        + navigate_into(int index) void
        + navigate_up() void
        + open_selected() void
        + run_command_in_current_dir(string cmd) void
        + last_command_result() const command_result
        + display_names() const vector~string~
        + selected_index() int*
        + current_path() const string

    }
    file_explorer_viewmodel --> file_system_model
    file_explorer_viewmodel --> os_service

    class os_service{
        <<interface>>
        +open_file(path) bool
        +run_command(cmd, cwd) command_result
    }
    class windows_os_service{
        +open_file(path) bool
        +run_command(cmd, cwd) command_result
    }
    class linux_os_service{
        +open_file(path) bool
        +run_command(cmd, cwd) command_result
    }
    os_service <|-- windows_os_service
    os_service <|-- linux_os_service

    class menu_panel{
        +menu_panel() Component
    }
    class path_bar{
        +path_bar() Component
    }
    class command_input{
        +command_input() Component
    }
    class tree_main{
        +build_main_tree() Component
    }
    tree_main -->menu_panel
    tree_main -->path_bar
    tree_main -->command_input

    menu_panel..>file_explorer_viewmodel
    path_bar..>file_explorer_viewmodel
    command_input..>file_explorer_viewmodel
```

## Component/Architecture Diagram
**Version 1.0**

```mermaid
flowchart TD
    main[Composition Root]
    main --> file_explorer_viewmodel
    main --> tree_main
    main --> windows_os_service
    main --> linux_os_service
    subgraph UI[UI Layer]
        tree_main
        menu_panel
        path_bar
        command_input
    end
    tree_main --> menu_panel
    tree_main --> path_bar
    tree_main --> command_input
    subgraph VM[ViewModel Layer]
        file_explorer_viewmodel
    end
    subgraph model[Model Layer]
        file_system_model
        dir_entry
    end
    subgraph services[Services Layer]
        os_service
        windows_os_service
        linux_os_service
        command_result
    end
    UI --> VM
    VM --> model
    VM --> services
```

## Sequence Diagram

### Navigating into a Directory
**Version 1.0**

```mermaid
sequenceDiagram
    User ->> menu_panel : Selects item in list
    menu_panel ->> file_explorer_viewmodel : open_selected()
    alt entry is directory
        file_explorer_viewmodel ->> file_explorer_viewmodel : navigate_into()
        file_explorer_viewmodel ->> file_system_model : list_directory()
        file_system_model -->> file_explorer_viewmodel : returns vector~dir_entry~
        file_explorer_viewmodel -->> menu_panel : update state
        menu_panel -->> User : re-renders menu
    else entry is file
        file_explorer_viewmodel ->> os_service : open_file(path)
        os_service -->> file_explorer_viewmodel : returns bool
    end
```

### Running a Shell Command

```mermaid
sequenceDiagram
    User ->> command_input : enters command
    command_input ->> command_input : on_enter() fires
    command_input ->> file_explorer_viewmodel : run_command_in_current_dir(cmd)
    file_explorer_viewmodel ->> os_service : run_command(cmd, cwd)
    os_service -->> file_explorer_viewmodel : returns command_result
    file_explorer_viewmodel ->> file_explorer_viewmodel : stores last_command_result_
    file_explorer_viewmodel -->> command_input : (call returns)
    command_input ->> file_explorer_viewmodel : last_command_result()
    file_explorer_viewmodel -->> command_input : returns command_result
    command_input -->> User : re-renders with result
```
This design is synchronous and may be blocking by design for now.

## State Diagram
**Version 1.0**
```mermaid
stateDiagram-v2
    [*] --> Menu
    Menu --> CommandInput : Pressing "3"
    CommandInput --> Menu : Pressing "2"
    Menu --> PathBar : Pressing "1"
    CommandInput --> PathBar : Pressing "1"
    PathBar --> Menu : Pressing "2"
    PathBar -->  CommandInput : Pressing "3"

    CommandInput --> InputState : Pressing Enter
    InputState --> CommandInput : Pressing Esc (Cancel)
    InputState --> CommandInput : Pressing Enter (Submit)
```

Needs updating with further input states (but this is the first iteration)