# README for Programming Assignment PA8

## Programming Assignment PA8

### Name: Adrian Olmos

### CruzID: amolmos

### Assignment: pa8

## Overview

This programming assignment, pa8, focuses on implementing and testing a Red-Black Tree-based Dictionary Abstract Data Type (ADT) for efficient data management and retrieval, with applications in word frequency analysis and data ordering.

## Files Included

- **DictionaryTest.cpp**: Test suite for all operations of the Dictionary ADT.
- **Dictionary.h**: Header file defining the interface for the Dictionary ADT.
- **Dictionary.cpp**: Implementation of the Dictionary ADT.
- **WordFrequency.cpp**: Main program utilizing the Dictionary ADT for word frequency analysis in a text file.
- **Order.cpp**: Reads a text file and outputs a list of words and their frequencies.
- **Makefile**: Compilation instructions for the project.
- **README.md**: This file, describing the project and its components.

## Descriptions

- **DictionaryTest.cpp**: Tests each function of the Dictionary ADT to ensure correctness and robustness.
- **Dictionary.h**: Outlines the structure and public functions of the Dictionary ADT.
- **Dictionary.cpp**: Implements the functionality of the Dictionary ADT, including insertion, deletion, search, and other utility functions.
- **WordFrequency.cpp**: Reads a text file, counts word occurrences using the Dictionary ADT, and outputs the frequency of each word.
- **Order.cpp**: Demonstrates the use of the Dictionary ADT in ordering and sorting data from a text file.
- **Makefile**: Provides commands for compiling the project, including separate targets for the main program and the test suite.
- **README.md**: Offers an overview and instructions for using the project files.

## Compilation

- Compile the project with the command `make`, which builds the Dictionary test suite and the main WordFrequency program, as well as the Order program.
- Individual compilation commands are also specified in the Makefile for convenience.

## Usage

- To run the Dictionary test suite: `./DictionaryTest`
- To execute the WordFrequency program: `./WordFrequency <input_file> <output_file>`
- To run the Order program: `./Order <input_file> <output_file>`

## Additional Notes

- The Makefile includes targets for compiling individual components and cleaning compiled binaries.
- The Dictionary ADT is implemented as a Red-Black Tree, offering efficient operations for data management.
- The WordFrequency program showcases the practical use of the Dictionary ADT in processing and analyzing text data.
- The Order program demonstrates how the Dictionary ADT can be used for data ordering and organization.
- The DictionaryTest suite is crucial for verifying the correctness and reliability of the ADT implementation.

## Contact

For any queries or issues related to this assignment, please contact Arthur Wei at hwei20@ucsc.edu.