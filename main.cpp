/** Filename: main.cpp
 * Description: main program logic for the linear algebra calculator
 * Author: Khoa Tran
 */

#include "matrix.hpp"
#include "interface.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/** Function: main
 * Description:
 * - provides main program logic
 * - takes the following command line args: -h, -d, -rref (see README for details)
 * Input: number of command line args (int), array of command line args (c-string)
 * Output: 0 (int), provided exit() is not called before the function's return
 */

int main(int argc, char **argv) {
    cout << endl;

    // store command line option, argument 1, and argument 2, respectively
    string option, arg1, arg2;

    // if there are more than 1 command line args, run the parser
    if (argc > 1) {
        if (!cmdArgsParser(argc, argv, option, arg1, arg2) ) { 
            cout << "Invalid command line arguments were provided! The program will exit.\n\n";
            exit(EXIT_FAILURE); 
        }

        // display instructions when "-h" option is passed
        if (option == "-h") {
            displayInstructions();
            exit(0); // exit for now
        }
    }
    else {
        cout << "For help, type \"help\" at the input prompt.\n\n";
        // for now, exit the program. Future implementations will allow the program to continue.
        // it will then ask the user to choose an operation, then ask for matrix(ces).
        exit(0);
    }
    
    // 2D vectors to store matrices
    vector <vector <double>> matrixA;
    vector <vector <double>> matrixB;
    
    // get matrix input again if it's not valid
    while (!matrixInputIsValid(arg1) ) {
        getMatrixFromUser(arg1);
    }

    // parse matrix input and store entries in matrix
    parseMatrixInput(arg1, matrixA);

    // if there is input for a second matrix, check and parse
    if (arg2 != "") {
        while (!matrixInputIsValid(arg2) ) {
            getMatrixFromUser(arg2);
        }

        parseMatrixInput(arg2, matrixB);
    }

    // perform operation according to the option passed
    executeOperation(option, matrixA, matrixB);

    return 0;
}