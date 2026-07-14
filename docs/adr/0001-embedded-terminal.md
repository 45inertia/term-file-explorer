# Embedded Terminal Implementation

Date: 14/07/2026

## Context
Having a run command feature is good for single, simple commands. But what should be done when the
user wants to run more complex commands like they would in a shell.

## Decision
Two approaches were considered:
### Shelling out a single command - **Selected**
This involves running the command, capturing the output and displaying the result. Simple and 
fits the sychronous render loop reasonably well.
### PTY Pseudo Terminal
This isn't just running a subprocess and capturing the final output, its emulating an interactive
terminal session:
- Bidirectional streaming I/O
- Handling ANSI escape codes for cursor movement/color
- Dealing with programs that expect a TTY and behave differently without one
- Keeping persistent shell process alive across multiple command
Implementing a proper PTY is also platform specific (Windows uses ConPTY, Linux uses 
forkpty/openpty).
An ANSI escape sequence parser is needed to interpret what the shell sends back and render it
correctly in FTXUI

## Consequences
The Embedded Terminal Implementation would add a lot of complexity so the first iteration of the
program will not include it and instead include **shelling out a single command**.

However I want to add this to a **future version** of the software and therefore it should be added 
as an issue that can be worked on in the future.