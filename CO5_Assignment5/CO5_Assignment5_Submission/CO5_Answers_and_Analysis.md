# CO5 Assignment 5 – Design Answers, Implementation and Experimental Notes

## Assignment title
**Reliable Software with Runtime Polymorphism and Exceptions**  
Course: Object Oriented Programming with C++ (DSA01)  
Course Outcome: CO5

## 1. Introduction and objectives
This assignment studies how a C++ billing application can process different bill and payer types through common interfaces, bind the correct operation at runtime, reject invalid claims, and recover safely from errors. The case study is a multi-speciality hospital billing system covering outpatient, inpatient, day-care and emergency bills, with self-pay, insurance and government scheme payers.

Objectives:
- Design abstract `Bill` and `Payer` interfaces.
- Apply virtual and pure virtual functions and runtime polymorphism.
- Explain early/late binding, vtables and virtual destructors.
- Design exception classes and decide where to throw, catch, log and rethrow.
- Use RAII to preserve resource safety during stack unwinding.
- Implement and test billing, payer and exception-handling programs.
- Compare alternatives using Big-O and measured timings.

Compiler verification: g++ 14.2.0; language standard C++17; compile command `g++ -std=c++17 -Wall -Wextra source.cpp -o program`. The performance experiment uses `-O2`.

## PART A – DESIGN

## A1. Design the polymorphic bill hierarchy

### A1.1 Common interface
Every bill needs a patient identifier/name and the common operations:
- `total() const`: calculates the payable bill amount.
- `type() const`: returns the bill category.
- `print() const`: prints the bill category, patient and total.

`total()` and `type()` are pure virtual because each bill category calculates its amount differently. `print()` can be a normal virtual function implemented once in the base class, because it uses the virtual operations.

### A1.2 Class hierarchy and UML
```text
                    Bill (abstract)
       patient      + virtual total() = 0
                    + virtual type() = 0
                    + virtual print()
                    + virtual ~Bill()
                 /       |       |        \
       OutPatientBill InPatientBill DayCareBill EmergencyBill
       consultation   days         package   baseCharge
       tests          perDay       price     hourlyRate, hours
```
All derived classes publicly inherit `Bill` and override `total()` and `type()`. The implementation is in `TaskA1/BillHierarchy.cpp`.

### A1.3 Process all bills pseudocode
```text
ALGORITHM CALCULATE_DAY_TOTAL(bills, count)
    dayTotal ← 0
    FOR index ← 0 TO count - 1
        currentBill ← bills[index]
        OUTPUT currentBill.type()
        OUTPUT currentBill.total()
        dayTotal ← dayTotal + currentBill.total()
    END FOR
    OUTPUT dayTotal
    RETURN dayTotal
END ALGORITHM
```
The code uses `vector<unique_ptr<Bill>>`, which owns the derived objects and processes them through the common base interface.

### Alternative: one structure and switch
A single record would store a type code and fields for all bill types. `total()` would switch on the type code. Processing n bills is O(n) in either design and one total calculation is O(1). The switch record may reserve fields unused by a particular bill. A new bill type requires modifying the switch and often the creation/validation logic. With the abstract base class, a new derived class implements the virtual functions while existing processing code remains unchanged.

## A2. Understand runtime binding

### A2.1 Early and late binding
A non-virtual member call is resolved using the static type at compile time (early binding). A virtual call through `Bill*` selects the final overrider according to the object's dynamic type at runtime (late binding). For example, `Bill* b = new OutPatientBill(...); b->total()` invokes `OutPatientBill::total()` when `total()` is virtual.

### A2.2 Conceptual vtable
```text
Bill vtable:
  total -> pure virtual entry
  type  -> pure virtual entry
  destructor -> Bill destructor

OutPatientBill vtable:
  total -> OutPatientBill::total
  type  -> OutPatientBill::type
  destructor -> OutPatientBill destructor

InPatientBill vtable:
  total -> InPatientBill::total
  type  -> InPatientBill::type
  destructor -> InPatientBill destructor
```
A compiler typically stores a hidden vptr in a polymorphic object. The exact vtable layout and ABI are implementation-specific; the diagram is conceptual. A call through a base pointer uses the dynamic object's virtual dispatch table to find the override.

### A2.3 Virtual destructor
`Bill` must have a virtual destructor because derived bill objects may be deleted through `Bill*`. Without a virtual base destructor, deleting a derived object through a base pointer has undefined behaviour and the derived destructor may not release owned resources. `virtual ~Bill() = default;` is used in the source files.

### Predict-output program
Expected output:
```text
500 ~OPBill ~Bill
```
`show()` is non-virtual, but it calls the virtual `total()` internally. Virtual dispatch still uses the dynamic type, so `OPBill::total()` returns 500. Deletion through `Bill*` invokes the derived destructor first, followed by the base destructor. Removing `virtual` from the base destructor makes deletion through `Bill*` undefined behaviour; do not rely on a particular output. Use AddressSanitizer on the target compiler to investigate the defect, but sanitizer output is environment-dependent.

### Alternative: dynamic_cast checks
The program could test the runtime type using `dynamic_cast` and call a corresponding derived method. With k bill types, a chain of tests may require up to O(k) casts per bill, while a virtual call is O(1) dispatch. A polymorphic object generally carries implementation-dependent vptr overhead; dynamic_cast does not remove the need for correct object lifetime management.

## A3. Design with abstract classes – Payer

### A3.1 Payer interface
`Payer` is abstract and declares `virtual double amountCovered(const Bill&) const = 0;`.
- `SelfPay`: covers the full bill total.
- `Insurance`: stores a cover limit and co-payment percentage; covered amount is the lesser of the limit and the insurer's percentage share.
- `GovernmentScheme`: stores fixed package amounts and applies the matching package rule.
The sample implementation is in `TaskA3/PayerHierarchy.cpp`.

### A3.2 Extension
`CorporateTieUp` derives from `Payer` and implements `amountCovered()` using a configured percentage. The existing payer classes and billing loop do not need modification.

### Alternative: function pointers or std::function
A policy function can be stored in a function pointer or `std::function`. Invoking the selected policy is O(1) in the usual model. A callable may capture data such as a cover limit, but the state must be stored in the callable/closure or in a separate configuration object. An abstract class groups policy state and behaviour in one named type and is convenient when payer types have different data and validation.

## A4. Design the exception strategy

### A4.1 Error conditions and hierarchy
Potential errors from the assignment:
- Negative bill charge or negative cover value.
- Claim amount greater than the policy cover.
- Unknown government package code.
- Missing patient record.
- Invalid numeric text (`std::invalid_argument` from `std::stod`).
- Numeric value outside allowed range (`std::out_of_range`).
- Memory allocation failure (`std::bad_alloc`).

Proposed hierarchy:
```text
std::exception
    |
std::runtime_error
    |
BillingError
   /       \
ClaimError  MissingPatientError
```
Standard exceptions such as `std::invalid_argument`, `std::out_of_range` and `std::bad_alloc` can also be caught through `std::exception`.

### A4.2 Throw specifications and noexcept
Validation and claim approval functions may throw and should not be marked `noexcept`. Destructors, cleanup functions and simple non-failing observers should not throw; a destructor is implicitly non-throwing unless specified otherwise. Throwing during stack unwinding can call `std::terminate`, so destructors should perform cleanup without propagating exceptions. `noexcept` should be used only when the function can genuinely guarantee it will not throw.

### Alternative: return codes
A function can return an enum status or `bool` and place the error message in an output parameter. Normal-path time remains O(1); error-path time is also O(1) for simple validation. Return-code designs require every caller to inspect and propagate the status and message, increasing code and the risk of ignored errors. They avoid exception propagation costs but can be suitable for frequent expected failures or APIs that require explicit status handling.

## A5. Design recovery and rethrowing

### A5.1 Where to catch
- Validate data close to the input/claim boundary and throw a specific exception.
- Catch at a layer that can add useful context, log the event and use `throw;` to preserve the original exception.
- Catch at the application boundary to report a clear user-facing rejection and keep the application loop running where safe.
- Do not catch an exception only to ignore it.

### A5.2 Stack unwinding and RAII
When an exception leaves a scope, automatic objects in that scope are destroyed in reverse construction order. RAII types such as `std::string`, `std::vector`, `std::unique_ptr` and file-stream objects release their owned resources in destructors. This protects resources when control leaves a function by exception. Raw pointers with manual `delete` in multiple catch blocks are fragile because each new error path creates another opportunity to miss cleanup.

### Predict-output program
Expected output:
```text
~f ~main caught 42
```
The local guard in `f()` is destroyed as the exception exits `f`. The guard in `main` is then destroyed as stack unwinding exits the try block. The statement `not printed` is skipped because the throw transfers control to a matching handler. The catch prints the integer value 42.

### Alternative: manual delete in catch blocks
Manual cleanup may have similar asymptotic runtime, but each catch path must release every acquired resource. Adding a new error path can introduce a leak if one cleanup branch is missed. RAII centralizes cleanup in object lifetime and is easier to maintain.

## PART B – IMPLEMENTATION AND EXPERIMENTAL INVESTIGATION

## B1. Implement and validate polymorphic billing

The completed program is `TaskB1/CompleteBillCode.cpp`. It implements the required TODOs:
- `Bill::total()` is pure virtual.
- `Bill::type()` is virtual and returns `"Bill"` by default.
- `OutPatient::total()` returns consultation plus tests and type `"OP"`.
- `InPatient::total()` returns days multiplied by per-day rate plus surgery and type `"IP"`.

Expected and verified output:
```text
OP Ravi: 1700
IP Meena: 47500
Total 49200
```
Hand verification: OP = 500 + 1200 = 1700. IP = 3 × 2500 + 40000 = 47500. Grand total = 1700 + 47500 = 49200.

Removing `virtual` from the pure virtual declaration makes it an ordinary non-virtual function, so `= 0` is not valid for a non-virtual member function. The compiler rejects the abstract-interface declaration.

### Alternative: templates
Templates can process each bill type in a separate typed container and avoid a virtual call. The per-bill arithmetic remains O(1), but separate containers make it harder to keep all bill types in one heterogeneous list and process them in one uniform loop. A variant or common wrapper can address heterogeneous storage with different trade-offs.

## B2. Engineer error conditions

The source `TaskB2/ClaimValidation.cpp` completes the claim-validation TODOs:
- Negative billed amount or cover throws `std::invalid_argument("negative amount")`.
- A bill above cover throws `ClaimError("exceeds cover")`.
- `settle()` logs the `ClaimError` and uses `throw;` to rethrow the same exception.
- The top-level loop catches the error and continues to the next test case.

Verified output:
```text
approved 40000
audit: exceeds cover
claim rejected: exceeds cover
error: negative amount
```
The first case is approved. The second is logged in the settlement layer and then caught by the caller. The third is rejected as invalid input before a `ClaimError` is thrown.

The assignment also asks for unknown package, invalid numeric text, allocation failure and destructor evidence. The package includes validation examples and source, but it does not force an enormous allocation because that can destabilize the runtime. To test allocation failure safely, use a controlled test harness and catch `std::bad_alloc`; the exact behaviour depends on operating-system memory limits. Run the sanitizer command on the target system and preserve its actual report rather than fabricating one.

### Rethrow distinction
`throw;` rethrows the currently handled exception without changing its dynamic type. `throw e;` throws a new exception object based on the static type of `e`; if `e` is a base-class reference to a derived exception, this can slice the exception and lose derived information.

### Alternative: std::optional
A validation function can return `std::optional<double>` where an empty optional indicates rejection. Both successful and rejected calls are O(1) for a fixed validation. Return-based handling avoids exception propagation, which can be beneficial when invalid claims are frequent (e.g. 50%). Exceptions are expressive for unusual failures and keep the normal path uncluttered. `optional` adds a small result-state representation; exact size is implementation-dependent. For 1,000,000 claims, the invalid percentages correspond to 0, 10,000 and 500,000 invalid records. The supplied source does not claim a full exception-vs-optional benchmark; that experiment should be measured on the submission computer.

## B3. Virtual functions vs switch vs exceptions – cost

The supplied benchmark `TaskB3/PerformanceComparison.cpp` compares a switch-based record with a polymorphic vector. Compile with:
```bash
g++ -std=c++17 -O2 -Wall -Wextra TaskB3/PerformanceComparison.cpp -o benchmark
```
Run with a bill count, e.g. `./benchmark 1000000`. It reports elapsed time for the switch loop and virtual loop. The included `benchmark_results.txt` records one local run for 1,000, 100,000 and 1,000,000 bills. These are illustrative measurements, not universal performance guarantees. Results vary with CPU, compiler, optimization, memory allocation and system load.

| Bills per design | Switch seconds | Virtual seconds |
|---:|---:|---:|
| 1,000 | 0.000002876 | 0.000002868 |
| 100,000 | 0.000352721 | 0.000441136 |
| 1,000,000 | 0.004629400 | 0.004378780 |

The measurements show both approaches are linear in the number of bills for this workload. Small timing differences are not enough to claim one design is always faster. The switch design has simple contiguous data and no per-object allocation in this test; the polymorphic version uses separately allocated objects, so its timing includes allocation/layout effects outside the timed loop but its traversal can incur pointer indirection.

For the assignment's requested 10,000,000-bill measurement, run the benchmark with `10000000` on a machine with sufficient memory. The polymorphic vector may require substantial memory because it owns one heap object per bill. Record the measured output from that machine.

### Engineering trade-off
Use virtual dispatch when the system needs extensible heterogeneous objects and new types should be added without modifying stable processing code. A switch or `std::variant` can be appropriate when the set of types is closed and value storage/locality matters. Measure the actual workload before choosing based on speed.

### Alternative: std::variant and std::visit
A `variant` stores one of the alternatives inline, with size approximately that of the largest alternative plus a discriminator and alignment padding. `std::visit` performs type-based dispatch without a base-class pointer per object. It can improve locality compared with separately allocated polymorphic objects, but the set of alternatives is closed in the variant type; adding a new alternative requires updating the variant and visitors.

## B4. Final engineering decision

### B4.1 Extension
`TaskB4/ProductionExtension.cpp` adds `TelemedicineBill` and `CorporatePayer` as new derived classes. Existing bill and payer classes are not modified. The vector of `unique_ptr<Bill>` processes both outpatient and telemedicine bills through the same interface.

### B4.2 Resource safety
The source programs use `unique_ptr` for polymorphic ownership and virtual destructors for base interfaces. The claim exception program demonstrates logging and rethrowing. AddressSanitizer can be run with:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer TaskB2/ClaimValidation.cpp -o claim_asan
./claim_asan
```
A clean report must be captured from the user's actual environment. No sanitizer report is fabricated in this package.

### B4.3 Production decision
A polymorphic `Bill`/`Payer` design is suitable when bill and payer categories are expected to grow and independent teams need to add new types. Exceptions are appropriate for invalid claims, missing records and exceptional infrastructure failures; routine business rejections may be better represented by explicit result/status types if they are common. Production readiness also requires persistent audit logging, transaction boundaries, input validation, access control, tests, monitoring and a policy for unknown package codes. Performance should be verified at the required 200,000 bills/day workload.

### Alternative: configuration-driven plug-ins
A rules/configuration design stores rates and package rules as data. Interpreting a rule may take O(r) time for r rules unless indexed/cached; a virtual call is O(1) dispatch before the actual bill arithmetic. Configuration allows non-code rate changes but requires strict schema validation, versioning, audit trails and safe rule evaluation. New structural behaviour may still need code. Plug-ins offer flexibility but add deployment and compatibility risks.

## 3. Conclusion
The assignment demonstrates how abstract base classes and virtual functions support extensible billing and payer models, while exception handling and RAII improve reliability. The completed code covers the core bill hierarchy, payer strategies, claim validation, rethrowing, a polymorphic billing example, a performance comparison and a new bill/payer extension. The benchmark values are environment-specific; additional requested stress tests and sanitizer evidence must be captured on the student's computer before final submission.

## 4. References and submission checklist
Primary reference: **Assignment 5 – CO5: Reliable Software with Runtime Polymorphism and Exceptions**, Object Oriented Programming with C++ (DSA01), supplied 16-page SIMATS assignment handout.

Submission checklist:
1. Create repository `DSA01-<RegisterNumber>-Assignment5`.
2. Upload one folder per task with C++ files, input files, output text and screenshots.
3. Include README with name, register number, compiler/version, compile command and run instructions.
4. Make at least one progressive commit per task.
5. Include Part A design diagrams, pseudocode and exception hierarchy.
6. Include Part B code, tests, predictions, outputs, timings and sanitizer reports.
7. Add faculty as collaborator if repository is private.
8. Put the working GitHub URL on the report cover page and submit through Google Classroom and SIMATS.
