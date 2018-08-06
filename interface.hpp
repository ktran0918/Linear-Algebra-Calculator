/** Filename: interface.hpp
 * Description: contains declarations of methods used to interact with the user (i.e., get, clean up, and validate input from the user)
 * Author: Khoa Tran
 */

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <vector>
#include <string>
#include <iostream>

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/** Function: displayInstructions
 * Description: display usage instructions to the user
 * TODO: method will not be called at the start of the program; instead, it will be called when the command line argument "-h" is passed.
 * Input: none
 * Output: none
 */
void displayInstructions();

/** Function: getMatrixFromUser
 * Description:
 * - get matrix input from user as a single string, in the following format:
 * 1. Elements are entered by row, each separated by a space."
 * 2. Each row is separated by a comma.
 * - get matrix input (string) from the user
 * - parse the matrix input for matrix entries
 * - convert the entries to doubles and push them to the 2D vector
 * TODO: (upcoming feature) take matrix input as a command line argument, preceded by the type of operation to be performed on the matrix (e.g. -d "1 2, 3 4" -- this will be interpreted as "calculate the determinant of this matrix")
 * Input: a 2D vector, representing a matrix (passed by reference)
 * Change: fill the input 2D vector with matrix entries
 * Output: none
 */
void getMatrixFromUser(vector <vector <double>> &matrix);

#endif