# Programming Assignment

### Name: Adrian Olmos

### CruzID: amolmos

### Assignment: pa7

## Files:

- **DictionaryTest.cpp**: Contains tests for all ADT operations of the Dictionary.
- **Dictionary.h**: Header file for the Dictionary ADT.
- **Dictionary.cpp**: Implementation of the Dictionary ADT.
- **Order.cpp**: The main program that utilizes the Dictionary ADT for sorting and outputting data.
- **Makefile**: Compilation instructions for the project.
- **README.md**: The project description file.

## Description:

- **DictionaryTest.cpp**: A test suite for the Dictionary ADT, verifying each function's correctness through a series of automated tests.
- **Dictionary.h**: Header file defining the interface for the Dictionary ADT, including function prototypes and the structure of the Dictionary.
- **Dictionary.cpp**: Implementation of the Dictionary ADT, providing functionality for managing a collection of key-value pairs with efficient insertion, deletion, and lookup operations.
- **Order.cpp**: Contains the main function for the Order program. It reads input lines, uses them as keys in the Dictionary, and associates them with line numbers as values. It outputs two string representations of the Dictionary.
- **Makefile**: Contains compilation instructions for the project. It defines how to compile and link the Dictionary ADT and its test suites along with the Order program.
- **README.md**: Provides an overview of the project, its structure, and its contents.

## Compilation:

To compile the project, use the command `make`. This will compile the Dictionary test program (`DictionaryTest`) and the main Order program using the Dictionary ADT.

## Usage:

- To run the Dictionary test program: `./DictionaryTest`
- To run the Order program: `./Order <input_file> <output_file>`

## Additional Information:

- The Makefile includes targets for compiling individual components as well as cleaning up compiled binaries.
- The Dictionary ADT is a core component of this project, enabling efficient management of key-value pairs with various operations like search, insert, delete, and traversal.
- The Order program demonstrates the practical application of the Dictionary ADT in sorting and organizing data from an input file and producing formatted output.
- The test program (`DictionaryTest`) provides a comprehensive evaluation of the ADT functionalities and should be used to verify the correctness of the ADT implementation.
