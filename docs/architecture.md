# Architecture <!-- omit from toc -->

## Contents <!-- omit from toc -->

- [Class Diagram](#class-diagram)
- [Component/Architecture Diagram](#componentarchitecture-diagram)
- [Sequence Diagram](#sequence-diagram)
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



        + navigate_into(int index) void
        + navigate_up() void
        + open_selected() void
        + run_command_in_current_dir(cmd) void
        + display_names() const vector~string~
        + selected_index() int*
        + current_path() const string

    }
    file_explorer_viewmodel --> file_system_model
    file_explorer_viewmodel --> os_service

    class os_service{
        <<interface>>
        +open_file(path) bool
        +run_command(cmd, cwd) int
    }
    class windows_os_service{
        +open_file(path) bool
        +run_command(cmd, cwd) int
    }
    class linux_os_service{
        +open_file(path) bool
        +run_command(cmd, cwd) int
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
        file_explorer_view_model
    end
    subgraph model[Model Layer]
        file_system_model
        dir_entry
    end
    subgraph services[Services Layer]
        os_service
        windows_os_service
        linux_os_service
    end
    UI --> VM
    VM --> model
    VM --> services
```

## Sequence Diagram

worth doing for navigation flow and the run-command flow 

## State Diagram
If the app has distict modes (browsing vs command input focused vs confirmation dialog), a state
diagram showing valid transitions can catch UI bugs before you write them.