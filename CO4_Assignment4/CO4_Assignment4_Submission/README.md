# CO4 Assignment 4 – C++ Source Code and Execution Evidence

**Course:** Object Oriented Programming with C++ (DSA01)  
**Assignment:** Designing Reusable Class Hierarchies  
**Standard:** C++17  
**Compiler used for verification:** g++ 14.2.0  
**Compile flags:** `-std=c++17 -Wall -Wextra`

## Important personalization before submission
Replace the name/register-number placeholders in your own report or README copy if required by your faculty. The assignment sheet requires the repository name:
`DSA01-<RegisterNumber>-Assignment4`

## Folder structure
- `Task01/` – Payroll hierarchy, overridden `pay()`, polymorphic staff processing.
- `Task02/` – Person, Student, Staff, TeachingAssistant and ResearchScholar; virtual inheritance.
- `Task03/` – Base/member construction, initializer lists, constructor/destructor trace.
- `Task04/` – Static vs dynamic binding, virtual destructor, slicing, smart pointers.
- `Task05/` – Cart, `this`, method chaining, object pointers/references and dynamic allocation.
- `Task06/` – Abstract Vehicle hierarchy, rental/return, late fee and ElectricBus extension.
- `screenshots/` – Source-code preview and captured execution-output image for each task.
- `CO4_Answers_and_Analysis.md` – Design explanations, predictions and complexity comparisons.

## Compile and run each task
Open a terminal in the assignment root and run (replace the path with the task source file):

```bash
g++ -std=c++17 -Wall -Wextra Task01/Task01_PayrollHierarchy.cpp -o task01
./task01
```

Repeat with the matching `.cpp` file for Task02 through Task06. On Windows PowerShell, run the executable as `./task01.exe` after compiling with `-o task01.exe`.

## GitHub submission checklist
1. Create a repository named `DSA01-<RegisterNumber>-Assignment4`.
2. Add the task folders, README, analysis file and screenshots.
3. Commit each task separately as you complete/verify it. The assignment explicitly requires progressive commits (at least one per task), not one final bulk upload.
4. Add your faculty as collaborator if the repository is private.
5. Paste the working repository URL on the assignment cover page and submit it through Google Classroom and SIMATS.

## Evidence note
The screenshots in this package are generated evidence panels from the included source files and the actual local compiler output. They are not photographs of your personal VS Code window. If your faculty specifically requires screenshots showing your own VS Code editor and terminal, open each `.cpp` file in VS Code, run it on your computer, and add those personal screenshots as additional evidence.
