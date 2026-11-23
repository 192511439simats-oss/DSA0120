# CO5 Assignment 5 – Reliable Software with Runtime Polymorphism and Exceptions

**Student:** Mohanarangan S.  
**Register Number:** 192511439  
**Department:** CSE  
**Course Outcome:** CO5

## Repository structure
- `Part-A/Design_Report.md`: A1–A5 design answers, pseudocode, diagrams and analysis.
- `Part-B/B1_polymorphic_billing.cpp`: virtual bill hierarchy and payer policies.
- `Part-B/B2_exception_tests.cpp`: validation, exception hierarchy, logging and rethrowing.
- `Part-B/B3_benchmark.cpp`: virtual dispatch, switch and `std::variant` timing comparison.
- `Part-B/B4_extension.cpp`: new bill and payer extension.
- `Screenshots/`: add genuine screenshots of source code and terminal execution here.

## Build
Use a C++17 compiler such as g++.

```bash
g++ --version
g++ -std=c++17 -Wall -Wextra Part-B/B1_polymorphic_billing.cpp -o b1
./b1
```

For memory-safety testing:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g Part-B/B1_polymorphic_billing.cpp -o b1_asan
./b1_asan
```

For the benchmark:
```bash
g++ -std=c++17 -O2 -Wall -Wextra Part-B/B3_benchmark.cpp -o benchmark
./benchmark
```

## Task result notes
- B1 demonstrates runtime polymorphism, virtual destructors and payer strategies.
- B2 demonstrates validation exceptions, catch/rethrow and top-level recovery.
- B3 compares equivalent bill-processing approaches and prints measured timings on the machine where it is run.
- B4 adds a new bill type and payer without editing existing bill or payer classes.

## Important submission notes
1. Run each program on your own computer and save the actual terminal output.
2. Capture real VS Code screenshots showing the source and execution output.
3. Add screenshots to `Screenshots/Source_Code/` and `Screenshots/Execution_Output/`.
4. Replace measured values in the report with your own run's results. Benchmark timings depend on hardware and compiler.
5. Create at least one Git commit for each task. Do not upload everything as a single final commit.
6. Create the GitHub repository named `DSA01-192511439-Assignment5`, then add its URL to your report and Google Classroom submission.
