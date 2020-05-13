/** Filename: interface.hpp
 * Description: contains declarations of methods used to interact with the user (i.e., get, clean up, and validate input from the user).
 * Author: Khoa Tran
 */

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "matrix.hpp"

#include <vector>
#include <string>
#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

/** Function cmdArgsParser
 * Description: parse command line arguments:
 * - place command line option and arguments into strings to be handled by the program 
 * Input: number of command line args (int), array of command line args (c-string), option (string), first argument (string), second argument (string)
 * Change: store option, first argument, and second argument
 * Output: none
 */
bool cmdArgsParser(int argc, char** argv, string &option, string &arg1, string &arg2);

/** Function: displayInstructions
 * Description: display usage instructions to the user.
 * Input: none
 * Output: none
 */
void displayInstructions();

/** Function: getMatrixFromUser
 * Description: get matrix input from the user
 * Input: matrix input (string) (passed by reference)
 * Change: take user input and store it in the matrix input string.
 * Output: none
 */
void getMatrixFromUser(string &matrixInput);

/** Function: matrixInputIsValid
 * Description: check if matrix input is valid, i.e., in the following format:
 * 1. Elements are entered by row, each separated by a space."
 * 2. Each row is separated by a comma.
 * - Append comma at the end of a valid string if necessary to help parsing
 * Input: matrix input (string)
 * Change: append comma at the end of a valid string
 * Output: boolean indicating whether matrix input is valid
 */
bool matrixInputIsValid(string &matrixInput);

/** Function: parseMatrixInput
 * Description: 
 * - parse the matrix input for matrix entries
 * - convert the entries to doubles and push them to the 2D vector
 * Input: matrix input (string) (passed by constant reference), matrix (2D vector)
 * Change: fill matrix
 * Output: none
 */
void parseMatrixInput(const string &matrixInput, vector <vector <double>> &matrix);

/** Function: executeOperation
 * Description: perform operation dictated by the command line option on the 2 matrices
 * - whether the second matrix is used depends on the type of operation performed
 * Input: command line option (string), 2 matrices
 * Output: none;
 */
void executeOperation(const string &option, const vector <vector <double>> &matrixA, const vector <vector <double>> &matrixB);

#endif