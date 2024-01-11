# WI24 - Assignment 1
## TODO: Update this README

Design, test, and build our own variant class!
#### Due Jan 24, 11:30pm (PST)

## Introduction

This assignment has three parts:

1. First, you're going to implement your own version of a `variant` class.
2. Second, you're going to implement tests to ensure that your class works correctly -- then check it into git.
3. The third part of this assignment is a "code review" -- where each student will code-review another student's work.

## Variant Class

C++ is a strongly-typed language. C++17 introduced support for dynamically-typed variables. As we discussed in lecture, the `std::variant` and `std::any` types give your C++ program considerable flexibility with few limitations . 

For instance, when using `std::variant`, you can specify the types you want to support like so:

```cpp
// This variant can hold an int, float or a std::string.
std::variant<int, float, std::string> theVariant;  
```

`std::variant`-based variables can hold any value of the specified types -- but only one at a time. It can be an `int` or a `float`, but not both simultaneously. Once you assign a value, the internal type of the `variant` changes accordingly. You ask a `std::variant` variable what type of value it currently holds -- which is represents as an ordinal value (`0..n`).

In this assignment, you're going to build your own (simplified) version of a `Variant` class. This will help you understand C++ better, as well as give you some practice with software design, testing, and code reviews.

> For this assignment, you may NOT use the C++ `std::variant` class as part of your design.

## `Variant` Class Requirements

### Acceptable Values

Your `Variant` class must be able to hold any of the following types: `int`, `float`, `const char*` (or `std::string`). You won't be asked to store user defined types (classes). 

Consider using an `enum class` to indicate what type your `Variant` is currently holding:

```
enum class VariantType { intType, floatType, stringType };
```

### Constructors

Your `Variant` class must define all the standard methods required by any class (discussed in lecture). In addition, you'll need one constructor for each allowable type:

```cpp
class Variant 
{
  // Add OCF methods...
  Variant(int aValue);
  Variant(float aValue);
  Variant(const char* aValue);
};
```

> NOTE: When storing values of type `const char*` -- consider whether you can store the pointer you're given, or whether you need to do a deep copy.

### Setters

You will implement the corresponding setter methods (operators):
```cpp
Variant& operator=(int aValue);
Variant& operator=(float aValue);
Variant& operator=(const char* aValue);
```
> NOTE: When storing values of type `const char*` -- consider whether you can store the pointer you're given, or whether you need to do a deep copy.

Consider calling these assignment operators to initialize your `Variant` in your constructors to reduce code duplication.

### Getters

Given a `Variant` variable, a caller may request a value from the `Variant` in any of the four given types:

```cpp
sometype asInt() const;      // Retrieve value as int, but don't change internal type
sometype asFloat() const;    // Retrieve value as float, but don't change internal type
sometype asString() const;   // Retrieve value as string, but don't change internal type
VariantType getType() const; // Get current type of variant
```

In the interface above, we've left the specific type to be returned from each method up to you (`sometype` is just a placeholder). Before making the obvious choice, consider how you're going deal with error handling. For example, consider the following scenario:

```cpp
ECE141::Variant theStringVariant("hello");
auto theInt = theStringVariant.asInt(); // Can't convert "hello" to an int, so what do we do?
```

We suggest you consider returning variation of `std::optional` for these getters.

### Comparison Operators

Objects of type `Variant` must be comparable. Implement all the basic comparison operators (`==`, `!=`, `<`, `<=`, `>`, `>=`). Remember: programmers are lazy, and prefer to write as little code as possible. Can you think of a way to write the least amount of code for your comparison operators?

### Streamable

The last feature to implement is to make your variable "output streamable".  Consider:

```
Variant theVariant("hello world");
std::cout << theVariant;
```

Implement this feature using the standard `friend` method:

```
friend std::ostream& operator<<(std::ostream& aStream, const Variant& aVar);
```

## Testing

Our auto-grader provides some basic validation of your code. But that's not a full test suite.

Your final task is to make your `Variant` class testable. In lecture, we provide a video that detailed how to use a simple testing framework called `Testable`. That class has been included in your assignment repository.  You're welcome to use that -- or the _much more powerful_ `gtest` class provided by Google.  Regardless of which you choose, in this step, you'll write tests to confirm that your `Variant` class is working as designed. The thoroughness and quality of the tests you write will be evaluated as part of your score for this assignment.

You should create a test for every method in the `Variant` interface. Sometimes it's convenient to write a single test method to test multiple things, but generally we write one test per method. (See our video about designing a testing system for how to integrate our `Testable` class into your solution. It's pretty easy to do.

As we discussed in lecture, it may also be easier to create a subclass of `Variant` (e.g. `TestVariant`) and put all your testing code and logic here. That keeps your original `Variant` class from test-related changes.

## Submitting your work
#### Due Jan. 24, at 11:30pm

Turn in your submission by pushing your work to GitHub. Each time you do so, your code will be auto-tested by, "Vlad-the-compiler". The results are visible on your GitHub page for the assignment. Vlad didn't get invited to any new-year's eve parties -- and is a bad mood. Make sure you turn your work in on time!

Also make sure that all of your code (`.h` and `.cpp` files) are in the `Source/` directory. Vlad will only compile code in this directory!

#### Grading
```python
Compiles test: 20pts
Compare test:  25pts
Values test:   30pts
Manual code review: 25pts
```

> In your project folder is a file called, "students.json". For each assignment, fill out the fields in that file, including your name, PID, and level of effort for the assignment. 
