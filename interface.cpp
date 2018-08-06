/** Filename: matrix.cpp
 * Description: contains definitions of methods used to interact with the user (i.e., get, clean up, and validate input from the user).
 * Author: Khoa Tran
 */

#include "interface.hpp"

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
 * Description: helper function to validateMatrixInput(); clean up input string for further validity check:
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
    while (i < inputStrLen) {
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
    }

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

/** Helper function: validateMatrixInput
 * Description: 
 * - helper function to getMatrixFromUser()
 * - validate matrix input (a string) from the user
 * - if string is not valid, return the appropriate error code:
 * 1 - string is empty
 * 2 - input contains invalid characters (those other than comma, period, space, and numbers)
 * 3 - input does not contain at least one numerical entry
 * - if string is valid, return 0; additionally, append a comma to the string is one is not available, so that the resultant string is compliant for parsing
 * Input: matrix input (string) (passed by reference)
 * Change: appends comma to the input string if found valid
 * Output: error code (int)
 */

int validateMatrixInput(string &matrixInput) {
    // check if the string is empty
    if (matrixInput == "") return 1;

    // clean up the string for further checks
    cleanUpMatrixInput(matrixInput);

    // calculate length of string to prevent redundant computation in further checks
    int inputStrLen = matrixInput.length();

    // if after clean-up, the string is empty, then the string did not have a number to start with
    if (inputStrLen == 0) { return 3; }
    
    int i;

    // check if there's an invalid character in the string (not a number, period, comma, or space)
    for (i = 0; i < inputStrLen; i++) {
        if (matrixInput[i] < 48 || matrixInput[i] > 57) {
            if (matrixInput[i] != '.' &&
                matrixInput[i] != ',' &&
                matrixInput[i] != ' ') {
                
                return 2;
            }
        }
    }

    // string has passed all checks
    // add a comma at the end of the string if one isn't there
    if (matrixInput[inputStrLen - 1] != ',') {
        matrixInput += ',';
    }

    return 0;
}

void getMatrixFromUser(vector <vector <double>> &matrix) {
    string matrixInput; // matrix input from the user
    string matrixEntry; // individual entry to be converted to double

    int inputError; // input error code
    
    cin.ignore(); // clear the input stream
    do {
        cout << "Enter your matrix: ";
        // get matrix input as a single string, with spaces
        getline (cin, matrixInput, '\n');
        cout << endl;

        inputError = validateMatrixInput(matrixInput);
        
        // print error according to error code
        switch (inputError) {
            case 1:
                cout << "You didn't give a matrix! Please try again.\n\n";
                break;
            case 2:
                cout << "Your matrix input contains invalid characters! Please check and try again.\n\n";
                break;
            case 3:
                cout << "Input matrix must have at least one numerical entry! Please try again.\n\n";
                break;
        }
    } while (inputError != 0);

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