# Namma Metro Smart-Card Assignment 1 (CO1) — Separate Task Programs

This package contains **12 independent C++ programs**. Each file has its own `main()` and can be compiled and executed separately.

## Folder structure
- `source/Task01.cpp` to `source/Task12.cpp` — separate source code for every task.
- `output/` — output captured after compiling and running each program.
- `screenshots/` — VS Code-style source and terminal previews for each task.

## Compile and run (Windows PowerShell)
Open the `source` folder in VS Code. For example, for Task 01:
```powershell
g++ -std=c++17 -Wall -Wextra Task01.cpp -o Task01.exe
.\Task01.exe
```
Repeat with the required task filename. Example: `Task12.cpp` and `Task12.exe`.

## Task 08 sample input
The program asks for zone, hour and balance. The included output uses sample input: `3 18 100`.

## Important assignment notes
- Task 04 and Task 05 are the supplied prediction programs; write your prediction before executing them, as required by the assignment.
- The assignment does not state the student/senior concession percentage. No percentage is silently assumed in these task programs. Confirm the intended rate with your faculty before adding it.
- The PNG files are VS Code-style illustrative previews generated from the source and captured output; they are not screenshots captured from a live VS Code session. For genuine evidence, run each file on your computer and capture your own editor and terminal using `Windows + Shift + S`.
- Tasks 01, 02, 03, 07, 10 and 11 also require written analysis in the Word report; code alone does not replace those explanations.

## Compiler
Tested with g++ using C++17: `g++ -std=c++17 -Wall -Wextra`.
