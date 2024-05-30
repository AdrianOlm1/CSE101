# Programming Assignment

### Name: Adrian Olmos

### CruzID: amolmos

### Assignment pa6

## Files:

-**Arithmetic.cpp**: Contains the main function for the Arithmetic program.
- **BigIntegerTest.cpp**: Contains tests for all ADT operations of the BigInteger.
- **BigInteger.h**: Header file for the BigInteger ADT.
- **BigInteger.cpp**: Implementation of the BigInteger ADT.
- **List.h**: Header file for the List ADT (used by BigInteger).
- **List.cpp**: Implementation of the List ADT.
- **ListTest.cpp**: Contains tests for all ADT operations of the List.
- **Makefile**: Compilation instructions for the project.
- **README.md**: The project description file.

## Description:

- **BigIntegerTest.cpp**: A test suite for the BigInteger ADT, verifying each function's correctness through a series of automated tests.
- **BigInteger.h**: Header file defining the interface for the BigInteger ADT, including function prototypes and the structure of the BigInteger.
- **BigInteger.cpp**: Implementation of the BigInteger ADT, providing functionality for large integer operations like addition, subtraction, multiplication, and comparison.
- **List.h** and **List.cpp**: Provide the necessary underlying list structure for the BigInteger ADT.
- **ListTest.cpp**: Contains tests for all ADT operations of the List.
- **Makefile**: Contains compilation instructions for the project. It defines how to compile and link the BigInteger ADT and its test suites.
- **README.md**: Provides an overview of the project, its structure, and its contents.
- **Arithmetic.cpp**: Contains the main function for the Arithmetic program.


## Compilation:

To compile the project, use the command `make`. This will compile the BigInteger test program (`BigIntegerTest`) using the BigInteger and List ADTs.

## Usage:

- To run the BigInteger test program: `./BigIntegerTest`

## Additional Information:

- The Makefile includes targets for compiling individual components as well as cleaning up compiled binaries.
- The BigInteger ADT is a core component of this project, enabling operations with large integers that exceed standard data type limits.
- The test program (`BigIntegerTest`) provides a comprehensive evaluation of the ADT functionalities and should be used to verify the correctness of the ADT implementation.
