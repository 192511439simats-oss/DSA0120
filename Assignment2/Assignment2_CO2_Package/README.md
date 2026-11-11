# Assignment 2 – CO2 (C++)

Register number: 192511439  
Department: CSE  
Repository name: `DSA01-192511439-Assignment2`  
Compiler: g++ with C++17

## Structure
- `source/Task01` ... `source/Task07`: separate source files for each question.
- `outputs/`: captured stdout text from each compiled program.
- `screenshots/`: illustrative VS Code-style source and terminal previews.
- `Assignment2_CO2_Answer_Report.docx`: written report.

## Compile and run
From a task folder, compile a file with:
```bash
g++ -std=c++17 -Wall -Wextra TaskXX.cpp -o TaskXX
```
Windows PowerShell:
```powershell
.\TaskXX.exe
```
For Q7, optionally provide the number of operations:
```powershell
.\Task07.exe 2000000
```

## Notes
- Q1 and Q5 have separate files for the supplied prediction program and the Complete the Code exercise.
- Q3 uses an illustrative tariff because the assignment does not specify courier prices.
- Q2 includes a commented unsafe dangling-reference example; it is intentionally not called.
- Q7 compares a shifting fixed array with a circular buffer. Benchmark results depend on hardware, compiler and optimisation settings.
- Screenshots in this package are illustrative VS Code-style previews generated from the source and captured program output. They are not actual screenshots from the student's computer. Replace/add genuine screenshots before submission if required.
- Make at least one progressive Git commit per task. Do not upload all work in one final commit.
