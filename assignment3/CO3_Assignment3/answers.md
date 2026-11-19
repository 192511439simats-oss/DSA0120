# CO3 Assignment 3 – Answers and Design Notes

## Q1 – Constructors and Constructor Overloading
`Book` has a default constructor, a title-only constructor and a title-plus-copies constructor.
The constructors use member initializer lists and delegation. Negative copy counts are changed
to zero, so an invalid count is never stored.

- The compiler supplies a default constructor only when no constructor is declared.
- Once any constructor is declared, the compiler does not automatically supply a default constructor.
- Initializer lists directly initialize members and are required for const/reference members.
- Members initialize in their declaration order, not the order written in the initializer list.
- `explicit` prevents unintended implicit conversion from one argument to the class type.
- Each object creation takes O(1) time and O(1) extra space for the fixed members.

## Q2 – Copy Constructors: Shallow and Deep Copies
The program uses a dynamically allocated array of strings. The copy constructor allocates a
separate array and copies each medicine. Copy assignment first creates a new array, then
releases the old array; this also protects against self-assignment.

- A shallow copy copies the pointer, so two objects own the same array. Both destructors then
  attempt to free the same memory, causing a double-free error.
- A deep copy gives each object independent storage.
- Rule of Three: if a class needs a destructor, copy constructor or copy assignment operator,
  it commonly needs all three.
- Copy constructor use cases: initialization from another object, pass-by-value, and return by
  value when copy elision does not remove the copy.
- Copying n medicine names takes O(n) time and O(n) additional space.
- `std::vector<std::string>` follows the Rule of Zero and manages its own memory.

## Q3 – Dynamic Constructors and Destructors
`Event` dynamically allocates a two-dimensional seat map. `book` changes `O` to `X`, and
`cancel` changes `X` to `O`. The destructor deletes every row and then the row-pointer array.

- Local and block-scope objects are destroyed automatically when their scope ends, in reverse
  construction order.
- A heap object remains alive until `delete` is called.
- Missing `delete` causes a memory leak. Using `delete` instead of `delete[]` for an array is
  undefined behaviour.
- A destructor has no parameters, has no return type and cannot be overloaded.
- For R rows and S seats, the map stores R×S characters plus R row pointers.
- Each seat access is O(1). The row-pointer design uses R+1 allocations; a single flat array
  needs one allocation and index `r*S+s`.

## Q4 – Arithmetic and Stream Operator Overloading
`Money` stores the complete amount as integer paise, avoiding floating-point rounding.
`+` returns a new object; `+=` modifies the current object and returns `*this` by reference.
The stream insertion operator `<<` is a non-member friend because the left operand is
`std::ostream`.

- `a + b` is evaluated as `a.operator+(b)` for this member overload.
- Arithmetic, comparison and stream operations take O(1) time and O(1) extra space.
- Multiplication of one money amount by another money amount is generally not meaningful;
  multiplication by a scalar quantity is more useful.
- The sample includes a paise carry test: Rs 0.75 + Rs 0.50 = Rs 1.25.

## Q5 – Increment, Comparison and Subscript Operators
Prefix `++` increments and returns the updated object by reference. Postfix `++` accepts a
dummy `int`, saves the old value, increments the object and returns the old copy.
`Playlist` has const and non-const subscript overloads and checks the index.

For `Counter c{5}`, `a = c++` stores 5 and changes c to 6; `b = ++c` changes c to 7 and
stores 7. Therefore the values are `5 7 7`. Prefix avoids creating the old-value copy.
Playlist access is O(1); checked access adds one bounds comparison.

## Q6 – Rules of Operator Overloading
The `Text` class owns a dynamic character array. It implements a deep-copy constructor,
copy assignment, destructor, concatenation, comparison and output.

- Operators that cannot be overloaded include `::`, `.`, `.*`, `?:` and `sizeof`.
- Precedence, associativity and number of operands cannot be changed.
- At least one operand must be a user-defined type.
- Assignment `operator=` must be a member function.
- A friend is useful when a non-member operator needs private access, as with stream output.
- Concatenating strings of lengths n and m takes O(n+m) time and O(n+m) result storage.
- `std::string` is normally preferred because it already manages memory safely.

## Q7 – Complex Number Class
A complex number is represented as `a + jb`, using two `double` values.

For `z1=a+jb` and `z2=c+jd`:
- Addition: `(a+c) + j(b+d)`
- Subtraction: `(a-c) + j(b-d)`
- Multiplication: `(ac-bd) + j(ad+bc)`
- Division: `((ac+bd)/(c²+d²)) + j((bc-ad)/(c²+d²))`
- Magnitude: `sqrt(a²+b²)`

The class supports default, real-only and real-plus-imaginary constructors. Division checks
whether the denominator is zero and throws `std::domain_error`.

Each arithmetic operation and magnitude calculation is O(1) time and O(1) space.
`std::complex<double>` provides tested standard operations and is preferable in production;
a custom class is useful for learning and domain-specific validation.

## Verification notes
Compile all programs using C++17. Run the programs on your own system and capture screenshots
of both source code and execution output. For memory investigations, compile with:

```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g Task02.cpp -o Task02_asan
./Task02_asan
```

Do not report measured timings or sanitizer findings unless you actually ran those experiments.
