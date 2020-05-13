# Linear Algebra Calculator
Questions or comments? Send them to program's author:

Khoa Tran &lt;trankho@oregonstate.edu&gt;.

Jump to [Version Updates](#version-updates)

## Description
The **Linear Algebra Calculator** is a command-line utility that performs various matrix operations, such as addition, subtraction, determinant, row reduction, eigenvalue/eigenvector, etc.

## Usage
The program will take matrix input in the following format:
1. Elements are entered by row, each separated by a space.
2. Each row is separated by a comma.
        
For example, the following example input:

    "1 2 3, 4 5 6, 7 8 9,"
    
*the last comma is optional

... will yield this matrix:

    1   |   2   |   3
    4   |   5   |   6
    7   |   8   |   9

It is up to the user to make sure the number of entries per row is consistent. If there are consistencies, the program will truncate or add 0's to rows, depending on whether the first row is shorter or longer than the inconsistent rows, respectively.

### Input Error Handling
The input parser will attempt to do a relatively thorough cleanup of messy input for parsing or reject incomprehensible input altogether. Below is a list of cleanup techniques employed:
* Redundant or dangling decimal points are truncated.
* Redundant or dangling spaces are truncated. Additionally, spaces at the beginning and end of input string are removed.
* Redundant or dangling commas are truncated. Additionally, commas at the beginning are removed.

Here are the types of input error that will cause the input to be rejected completely:
* Input is empty.
* Input has invalid characters (non-number characters&mdash;except comma, space, or period).
* Input has no numbers.

The user will be asked to reenter when their input is rejected.

### Command line arguments
Command line arguments is a planned feature that will be implemented very soon. Here is a list of command line arguments that can be passed to the program:
* -h: display manual, the end of which the user will be given the option to run the core program
* -d [matrix input]: calculate the determinant of the given matrix
* -rref [matrix input]: row reduce to RREF
* -eval [matrix input]: calculate the eigenvalue
* -evec [matrix input]: calculate the eigenvector
* -null [matrix input]: find the basis for the null space
* [matrix input] + [matrix input]: add two matrices
* [matrix input] - [matrix input]: subtract the second matrix from the first
* [matrix input] * [matrix input]: multiply 2 matrices
* More command line options will be created if more features are implemented.

## Linear Algebra Operations
Here is a list of planned features:
* Determinant
* Addition and multiplication
* Row reduction to row-reduced echelon form (RREF)
* Eigenvalues and eigenvectors
* Null space
* More features?...

## Version Updates
(Version 1.0)

### 1. Implemented Features
* Matrix input error handling and parsing
* Calculating the determinant

### 2. To do soon:
* Check that matrix is square before calculating the determinant and eigenvalue (planned feature).
* [Command line arguments](#command-line-arguments)
* Row reduction to RREF

### 3. Tentative major feature:
* Take matrices from a file input and let the user choose which operations to perform on which matrices.

## Compilation
Run 'make'. Compiler: g++ c++11 standard.