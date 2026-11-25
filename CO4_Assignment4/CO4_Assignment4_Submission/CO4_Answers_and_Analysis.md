# CO4 Assignment 4 – Design Answers and Complexity Notes

## Task 1 – Class Design Review

### 1.1 Design deficiencies
1. `name`, `id` and `basic` are repeated in multiple classes.
2. Data members are public, so invalid values can be assigned without validation.
3. The same information uses inconsistent names (`name`/`nm`, `id`/`code`).
4. `da` is declared but not used in the pay calculation.
5. The 0.42 allowance rate is a magic number.
6. A new staff type requires another independent class and changes to code that processes staff.
7. There is no common base type, so all staff cannot be processed uniformly through one polymorphic loop.

### 1.2 Repaired hierarchy
`Staff` is an abstract base class containing common identity and basic-pay data. `Professor`, `LabAssistant` and `GuestFaculty` publicly inherit from it and override `pay()`. The example implementation stores `unique_ptr<Staff>` in one vector and calls `display()` through base pointers.

```text
             Staff (abstract)
             + name, id, basic
             + virtual pay() = 0
                /    |      \
       Professor  LabAssistant  GuestFaculty
       + research               + hours, rate
```

### 1.3 Design defence
Common staff information and the common interface are defined once in `Staff`. Each category implements its own pay rule. To add a new category, derive a new class and override `pay()`; the existing loop can continue to process it through `Staff` pointers without knowing its concrete type.

### Alternative and complexity
Both a `switch` implementation and a virtual `pay()` call take O(1) time per call. A single class with all category-specific fields may waste space because each object reserves fields it does not use. With inheritance, each object stores only its relevant derived data (plus implementation-dependent polymorphic overhead). A switch design generally requires editing the switch and possibly validation/creation logic for every new category; the polymorphic design localizes the new behaviour in a new derived class.

## Task 2 – From Requirement to Hierarchy

### 2.1 Relationships
- `Student is-a Person`: public, virtual inheritance.
- `Staff is-a Person`: public, virtual inheritance.
- `TeachingAssistant is-a Student` and `is-a Staff`: public multiple inheritance.
- `ResearchScholar is-a Student`: public multilevel inheritance.
- A `Person` may have an `Address` as a member: composition (has-a), not inheritance.

The combined structure is hybrid inheritance. The `Person` base is virtual in both `Student` and `Staff` so a `TeachingAssistant` contains one shared `Person` subobject.

### 2.2 Diamond problem
Without virtual inheritance, `TeachingAssistant` would contain one `Person` subobject through `Student` and another through `Staff`. Access to a common member such as `name` could become ambiguous and duplicate the base state. Virtual inheritance makes both paths share one virtual `Person` base. The most-derived class (`TeachingAssistant`) initializes that virtual base.

### 2.3 Class declarations
See `Task02/Task02_UniversityHierarchy.cpp`. `Student` and `Staff` virtually and publicly inherit `Person`; `TeachingAssistant` publicly inherits both; `ResearchScholar` publicly inherits `Student`.

### 2.4 Access table (Person member as seen in Student)
| Person member | Public inheritance | Protected inheritance | Private inheritance |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | Not directly accessible | Not directly accessible | Not directly accessible |

### Predict the output (virtual diamond)
```text
Person Student Staff TA
```
`Person` is initialized once because it is a virtual base. Virtual bases are initialized before non-virtual direct bases, and the most-derived constructor initializes them. If `virtual` is removed, two `Person` subobjects are constructed, so the trace becomes `Person Student Person Staff TA` for the simple trace structure. A compiler may also report ambiguity when an unqualified inherited `Person` member is accessed.

### Composition alternative and complexity
Composition would place separate `Student` and `Staff` member objects inside `TeachingAssistant`. It is a has-a design rather than an is-a design and may contain two `Person` subobjects unless the contained objects share state through another design. Access becomes explicit (`student.name` or `staff.name`) rather than a shared base member. Object size is implementation-dependent; compare using `sizeof` on the target compiler. Access is O(1) in either design, but composition avoids inherited-member ambiguity by requiring a named member path.

## Task 3 – Constructors and Member Classes

### 3.1 Initializer-list rule
The derived constructor initializes its direct base classes in the initializer list. In a virtual-inheritance diamond, only the most-derived class controls initialization of the virtual base; intermediate constructors' virtual-base initializers are ignored when those classes are subobjects of a more-derived object.

### 3.2 Member classes
`Address` is a member object of `Person`; the constructor initializes it in `Person`'s initializer list. `Student` initializes the `Person` base and its own members in its initializer list. The code demonstrates this with `Address home` and `Person(n, a, city, pin)`.

### 3.3 Construction/destruction order
For the supplied `Car` example, the exact output fragment is:
```text
Vehicle Engine Car | ~Car ~Engine ~Vehicle
```
Base classes are constructed first, then member objects in their declaration order, then the derived constructor body. Destruction is the reverse: derived destructor body, members in reverse declaration order, then base classes in reverse construction order.

### Complete-code constructor
The required initializer list pattern is:
```cpp
Student(const std::string& n, int a, long long r,
        const std::string& city, int p)
    : Person(n, a), regNo(r), home(city, p) {}
```
The included implementation also includes `Address` in `Person` and a course member to show member initialization. The expected sample record is `192311001 Kavya (19) Salem-636001 CSE`.

### Alternative pointer-to-Address design
A pointer member adds dynamic allocation and requires ownership rules. The constructor must allocate (or accept) the `Address`; the destructor must `delete` it; and the copy constructor/assignment must perform a deep copy or use an ownership type such as `std::unique_ptr` (which disables copying unless custom copy behaviour is supplied). Allocation/deallocation are typically O(1), but introduce allocation overhead and failure/ownership risks. An embedded member avoids separate allocation and has simpler value semantics.

## Task 4 – Pointers to Derived Classes

### 4.1 Defects
- `rate()` is non-virtual, so `Account*` calls `Account::rate()` (static binding).
- Deleting a `SeniorAccount` through `Account*` is undefined behaviour if the base destructor is not virtual.
- `history` is dynamically allocated and must be released by the derived destructor; without correct virtual destruction that destructor may not run.
- `Account copy = SeniorAccount()` slices the derived object, retaining only the `Account` base subobject.

### 4.2 Evidence
The repaired code prints both the non-virtual and virtual call results and adds destructor messages. Optional sanitizer verification command:
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer Task04/Task04_Polymorphism.cpp -o task04_asan
./task04_asan
```
Run this on the target system to capture its sanitizer report. Sanitizer output can vary by compiler/runtime.

### 4.3 Repair and 4.4 prevention
Declare polymorphic operations `virtual`, use `override` in derived classes, give a polymorphic base a `virtual` destructor, and store owning polymorphic objects using `std::unique_ptr<Account>`. Use references/pointers to preserve dynamic type instead of copying derived objects into base values.

### Predict the output
```text
3.5 4 3.5
```
`p->rate()` calls the non-virtual base function because the static type of `p` is `Account*`. `p->vrate()` dispatches at runtime to `SeniorAccount::vrate()`. `copy.vrate()` prints 3.5 because `Account copy = s` slices the derived object and creates a standalone `Account`.

### unique_ptr alternative and complexity
A `vector<unique_ptr<Account>>` provides automatic lifetime management and avoids manual `delete`. Processing n accounts remains O(n), with O(1) dispatch per account. Smart pointers do not by themselves prevent non-virtual functions from using static binding or object slicing if the program still copies objects into base values. A virtual base destructor remains necessary.

## Task 5 – Pointers to Objects and `this`

### 5.1 Four access forms
The code demonstrates direct object access (`c.add()`), pointer access (`pointer->add()`), reference access (`reference.total()`), and dynamic allocation (`new` followed by `delete`). `this` points to the current object. `return *this` returns that object by reference and enables chaining. `this->discount` distinguishes the data member from the parameter with the same name.

### 5.2 Highest total
The code creates an array of `Cart*`, scans it once and remembers the index of the largest total. This takes O(n) time and O(1) extra search space.

### 5.3 Comparison
A named local object has automatic lifetime and is usually safest for local use. A reference aliases an existing object and cannot be reseated. A non-owning pointer can be null and must not outlive its target. A pointer returned by `new` requires matching ownership and deletion; prefer smart pointers in production code. `*this` is an lvalue expression referring to the current object.

### Complete-code output
```text
324.00
```
`60 + 120 + 180 = 360`; a 10% discount gives `360 × 0.90 = 324`. If `add()` returned `Cart` by value, each chained call would operate on/copy a temporary result rather than returning the same object by reference; it would add unnecessary copies and could leave the original cart unchanged depending on implementation.

### vector<Cart> alternative
Finding the highest total remains O(n) in both an array of pointers and `vector<Cart>`. A vector of objects stores the objects directly; a pointer array stores one pointer per element plus separately allocated objects. Vector reallocation can invalidate pointers, references and iterators to its elements. Reserving capacity or using stable ownership containers can address some invalidation concerns.

## Task 6 – Vehicle Rental Fleet

### Stage 1 – Entities and testable requirements
Entities: `Vehicle`, `Bicycle`, `TwoWheeler`, `Car`, `ElectricCar`, and the extension `ElectricBus`. Common data are registration and daily rate. Special data include fuel level, seating capacity and battery capacity. Different vehicle types calculate charges differently. The fleet must list, rent, return and support new derived vehicle types.

Testable requirements:
1. Every vehicle exposes registration, type and charge calculation.
2. The fleet can list all vehicles through base-class pointers.
3. Renting changes the vehicle status to rented.
4. Returning changes the status to available and applies a late fee.
5. Adding a new derived vehicle does not require changing existing vehicle classes.

### Stage 2 – Hierarchy
```text
             Vehicle (abstract)
       registration, dailyRate, rented
          charge(days) = 0
          type() = 0
        /       |        |        \
   Bicycle  TwoWheeler   Car    ElectricBus
                            |
                       ElectricCar
```
`Vehicle` is an abstract base class. `ElectricCar` is a specialized `Car`; all other listed types publicly inherit from `Vehicle`.

### Stage 3 – Decisions
Common data and rent/return/list operations belong in `Vehicle`. `charge()` and `type()` are pure virtual functions. The fleet uses `vector<unique_ptr<Vehicle>>` to own objects safely and process them polymorphically.

### Stage 4 – Pseudocode
```text
ALGORITHM RENT(vehicle)
    vehicle.rent()
END ALGORITHM

ALGORITHM RETURN(vehicle, lateDays)
    charge ← vehicle.returnVehicle(lateDays)
    OUTPUT charge
END ALGORITHM

ALGORITHM LIST_FLEET(fleet)
    FOR EACH vehicle IN fleet
        vehicle.list()
    END FOR
END ALGORITHM
```

### Stage 5 – Implementation
The complete executable is `Task06/Task06_VehicleRentalFleet.cpp`. It demonstrates all four requested types and an additional `ElectricBus`, rents and returns a car, and applies a late fee. The example late fee is ₹200 per late day (an implementation assumption for demonstration because the assignment does not prescribe a numeric fee).

### Alternative single-class/switch design
A switch-based `charge()` and a virtual `charge()` call are both O(1) per vehicle. A single class may reserve fields unused by some vehicle categories; a polymorphic design stores only relevant derived data plus implementation-dependent virtual-dispatch overhead. With a switch, adding a type requires editing the switch and likely construction/validation logic. With the hierarchy, a new derived class can implement the required virtual functions without modifying existing vehicle classes.

## Submission reminder
The assignment requires progressive Git commits (at least one per task), a working GitHub repository link, screenshots of code and execution output, and submission through both Google Classroom and SIMATS. Verify the actual repository URL and upload process yourself before submitting.
