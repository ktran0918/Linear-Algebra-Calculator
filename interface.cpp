/** Filename: matrix.cpp
 * Description: contains definitions of methods used to interact with the user (i.e., get, clean up, and validate input from the user).
 * Author: Khoa Tran
 */

#include "interface.hpp"

bool cmdArgsParser(int argc, char** argv, string &option, string &arg1, string &arg2) {
    if (argc == 2) {
        option = argv[1];
    }

    else if (argc == 3) {
        if (argv[1][0] == '-') {
            option = argv[1];
            arg1 = argv[2];
        }
        else if (argv[2][0] == '-') {
            option = argv[2];
            arg1 = argv[1];
        }
        else {
            return false;
        }
    }

    else if (argc == 4) {
        if (argv[2][0] == '+' ||
            argv[2][0] == '-' ||
            argv[2][0] == '*') {
                option = argv[2];
                arg1 = argv[1];
                arg2 = argv[3];
        }
        else {
            return false;
        }
    }

    else { return false; }

    return true;
}

void displayInstructions() {
    // print usage instructions (also found in the program's documentation)
    cout << "\n\t\tWELCOME TO THE LINEAR ALGEBRA CALCULATOR!\n"
        << "Questions or comments? Send them to program's author:\n"
        << "Khoa Tran <trankho@oregonstate.edu>.\n\n";

    cout << "The program will take matrix input in the following format:\n"
        << "\t1. Elements are entered by row, each separated by a space.\n"
        << "\t2. Each row is separated by a comma.\n\n"
        << "The following example input...\n\n"
        << "1 2 3, 4 5 6, 7 8 9," << "\t*Comma is optional to end the last row\n\n"
        << "... will yield this matrix:\n\n"
        << "1 | 2 | 3\n"
        << "4 | 5 | 6\n"
        << "7 | 8 | 9\n\n";

    cout << "Make sure the number of entries per row is consistent. Inconsistencies will result in row entries being truncated or appended with 0's!\n\n";

    // ask the user whether to run the core program after reading the instructions
    string userContinue;
    cout << "Enter 'y' to start the program: ";
    cin >> userContinue;

    // if anything else other than 'y' is entered, exit without errors
    if (userContinue != "y")
        exit(0);
    
    cout << endl;
}

/** Helper function: cleanUpMatrixInput
 * Description: helper function to matrixInputIsValid(); clean up input string for further validity check:
 * - Remove dangling and duplicate periods (decimal points)
 * - Remove spaces at the beginning and end of input; remove multiple spaces in a row
 * - Remove commas at the beginning of input; remove multiple commas in a row
 * Input: matrix input (string) (passed by reference)
 * Change: trim input string as necessary
 * Output: none
 */

void cleanUpMatrixInput(string &matrixInput) {
    int inputStrLen = matrixInput.length();
    int i = 0;

    // remove dangling and duplicate periods
    /*while (i < inputStrLen) {
        // if a period is encountered with a successive period or comma, delete the current period
        if (matrixInput[i] == '.' && (matrixInput[i+1] == '.' || matrixInput[i+1] == ',') ) {
            // erase the period at iterator; i is kept in place to check the next character, which is shifted over after erase
            matrixInput.erase(matrixInput.begin() + i);
            inputStrLen -= 1;
        }
        // if a period is encountered with a successive space, delete the space (the next character)
        else if (matrixInput[i] == '.' && matrixInput[i+1] == ' ') {
            // erase the next character
            matrixInput.erase(matrixInput.begin() + i + 1);
            inputStrLen -= 1;
        }
        // if the period is next to a number, or the current character is something else entirely, do nothing and move on to the next character
        else { i++; }
    }*/

    // if all dangling and duplicate periods have been deleted, but all the string has left is a single period, input is meaningless; delete the last period and do nothing more.
    if (inputStrLen == 1 && matrixInput[0] == '.') {
        matrixInput.erase(0);
        return;
    }

    // remove spaces and commas at the beginning
    while (matrixInput[0] == ' ' || matrixInput[0] == ',') {
        matrixInput.erase(matrixInput.begin());
    }
    // remove spaces at the end
    while (matrixInput.back() == ' ') {
        matrixInput.erase(matrixInput.end() - 1);
    }

    // recalculate length
    inputStrLen = matrixInput.length();

    // after cleanup, if the string is empty, this means the string did not have numbers to start with; nothing more can be done.
    if (inputStrLen == 0) { return; }

    // begin removing redundant spaces and commas
    i = 1; // start at 1 since the string now has no spaces or commas at the beginning
    while (i < inputStrLen) {
        // remove spaces in a row, as well as spaces before commas
        if (matrixInput[i] == ' ' && (matrixInput[i+1] == ' ' || matrixInput[i+1] == ',') ) {
            matrixInput.erase(matrixInput.begin() + i);
            inputStrLen -= 1;
        }
        // remove commas in a row, as well as spaces after commas
        else if (matrixInput[i] == ',' && (matrixInput[i+1] == ',' || matrixInput[i+1] == ' ') ) {
            // remove the next character to avoid erasing the current comma, which might be important
            matrixInput.erase(matrixInput.begin() + i + 1);
            inputStrLen -= 1;
        }
        else { i++; }
    }

    cout << "Input has been cleaned up to be: " << matrixInput << "\n\n";
}

bool matrixInputIsValid(string &matrixInput) {
    // check if the string is empty
    if (matrixInput == "") {
        cout << "You didn't give a matrix! Please try again.\n\n";
        return false;
    };

    int i;

    // calculate length of string to prevent redundant computation in further checks
    int inputStrLen = matrixInput.length();

    // clean up the string for further checks
    cleanUpMatrixInput(matrixInput);

    /*for (i = 0; i < inputStrLen; i++) {
        if (matrixInput[i] == '-') {
            if ( isdigit(matrixInput[i-1]) ||
                !isdigit(matrixInput[i+1]) ) {
                    cout << "Input is invalid because it contains dangling negative signs! Please check again.\n\n";
                    return false;
            }
        }
    }

    for (i = 0; i < inputStrLen; i++) {
        if (matrixInput[i] == '.') {
            if ( (isdigit(matrixInput[i-1]) && matrixInput[i+1] != ' ' && matrixInput[i+1] != ',') ||
                (isdigit(matrixInput[i+1]) && matrixInput[i-1] != ' ' && matrixInput[i-1] != ',' && matrixInput[i-1] != '-') ) {
                    cout << "Input is invalid because it contains dangling decimal points! Please check again.\n\n";
                    return false;
            }
        }
    }*/

    // calculate length of string to prevent redundant computation in further checks
    inputStrLen = matrixInput.length();

    // if after clean-up, the string is empty, then the string did not have a number to start with
    if (inputStrLen == 0) {
        cout << "Input matrix must have at least one numerical entry! Please try again.\n\n";
        return false;
    }

    // check if there's an invalid character in the string (not a number, period, comma, or space)
    for (i = 0; i < inputStrLen; i++) {
        if (matrixInput[i] < 48 || matrixInput[i] > 57) {
            if (matrixInput[i] != '.' &&
                matrixInput[i] != ',' &&
                matrixInput[i] != ' ' &&
                matrixInput[i] != '-') {
                
                cout << "Your matrix input contains invalid characters! Please check and try again.\n\n";
                return false;
            }
        }
    }

    // string has passed all checks
    // add a comma at the end of the string if one isn't there
    if (matrixInput[inputStrLen - 1] != ',') {
        matrixInput += ',';
    }

    return true;
}

void getMatrixFromUser(string &matrixInput) {
    //cin.ignore(); // clear the input stream
    cout << "Enter your matrix: ";
    // get matrix input as a single string, with spaces
    getline (cin, matrixInput, '\n');
    cout << endl;
}

void parseMatrixInput(const string &matrixInput, vector <vector <double>> &matrix) {
    string matrixEntry; // individual entry to be converted to double
    
    // calculate input string length to prevent redundant calculations
    int inputStrLen = matrixInput.length();
    // row of entries to be pushed to the matrix vector
    vector <double> rowEntries;

    int i = 0, j = 1;

    /* begin parsing
    - 2 iterators: one to track the beginning of an entry; the other to track the end */
    for (j = 0; j < inputStrLen; j++) {
        // if a space character is encountered, and if the preceding character isn't another space or a comma, extract the substring (row entry)
        if (matrixInput[j] == ' ') {
            if (matrixInput[j-1] != ' ' && matrixInput[j-1] != ',') {
                matrixEntry = matrixInput.substr(i, j-i);
                //cout << matrixEntry << endl; // for checking
                // convert the row entry to a double and push it to a row
                rowEntries.push_back(stod(matrixEntry));
                
                i = j + 1; // move the beginning iterator to where the end iterator is, plus one
            }
        }

        // if a comma character is encountered, and if 
        else if (matrixInput[j] == ',') {
            if (matrixInput[j-1] != ',') {
                matrixEntry = matrixInput.substr(i, j-i);
                //cout << matrixEntry << endl;
                rowEntries.push_back(stod(matrixEntry));
                matrix.push_back(rowEntries);
                rowEntries.clear();
            }
            
            i = j + 1;
        }
    }
}

void executeOperation(const string &option, const vector <vector <double>> &matrixA, const vector <vector <double>> &matrixB) {
    if (option == "-d") {
        printMatrix(matrixA);
        
        if (matrixIsSquare(matrixA)) {
            cout << "Determinant: " << determinant(matrixA, matrixA.size() ) << "\n\n";
        }
        else {
            cout << "Matrix is not square! Determinant cannot be calculated.\n\n";
        }
    }
    else if (option == "-rref") {
        printMatrix(matrixA);
        cout << "RREF:\n\n";
        printMatrix( rref(matrixA) );
    }
}