# CO5 Assignment 5 – Runtime Polymorphism and Exceptions

**Course:** Object Oriented Programming with C++ (DSA01)  
**Assignment:** Reliable Software with Runtime Polymorphism and Exceptions  
**Compiler verified:** g++ 14.2.0  
**Language standard:** C++17  
**Standard compile command:** `g++ -std=c++17 -Wall -Wextra file.cpp -o program`

## Contents
- `TaskA1/` – Abstract Bill hierarchy and polymorphic daily total.
- `TaskA2/` – Runtime binding and virtual destructor demonstration.
- `TaskA3/` – Abstract Payer hierarchy and CorporateTieUp extension.
- `TaskA4/` – Billing exception types and validation.
- `TaskA5/` – Stack unwinding, RAII and exception recovery.
- `TaskB1/` – Completed bill hierarchy TODO program.
- `TaskB2/` – Claim validation, logging and rethrowing TODO program.
- `TaskB3/` – Switch versus virtual dispatch benchmark and measured sample output.
- `TaskB4/` – Extension with TelemedicineBill and CorporatePayer.
- `screenshots/` – Source-code previews and execution-output screenshots.
- `CO5_Answers_and_Analysis.md` – Part A and Part B design answers, pseudocode, predictions, complexity notes and experiment discussion.

## Compile and run
Example:
```bash
g++ -std=c++17 -Wall -Wextra TaskB1/CompleteBillCode.cpp -o taskb1
./taskb1
```
Repeat for each `.cpp` file. For the benchmark, use `-O2`:
```bash
g++ -std=c++17 -O2 -Wall -Wextra TaskB3/PerformanceComparison.cpp -o benchmark
./benchmark 1000000
```
For AddressSanitizer:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer TaskB2/ClaimValidation.cpp -o claim_asan
./claim_asan
```

## Personalize before submission
Update your name, register number, faculty name and GitHub repository URL on the Word report cover page and README if required.

## Important evidence limitations
The screenshots are generated evidence panels based on the included source files and actual program output. They are not photos of your personal VS Code window. Add screenshots from your own VS Code/editor and terminal if your faculty requires that.
The included performance timings are one local illustrative run for 1,000, 100,000 and 1,000,000 bills. The assignment also requests 10,000,000-bill measurements, exception-vs-return-code tests at multiple invalid rates, and AddressSanitizer evidence. Those are not fabricated here; run them on your laptop and add the actual measurements/reports before submission. The package does not force an enormous memory allocation for `std::bad_alloc`, because that can destabilize the computer.
