/** Filename: matrix.hpp
 * Description: Library declaration for useful matrix methods and linear algebra operations
 * Author: Khoa Tran
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

using namespace std;

/** Function: printMatrix
 * Description: print a given matrix
 * Input: 2D vector representing a matrix (passed by constant reference)
 * Output: none
 */
void printMatrix(const vector <vector <double>> &matrix);

/** Function: determinant
 * Description: calculate the determinant of a given matrix
 * Input: 2D vector representing a matrix (passed by constant reference)
 * Output: determinant of a given matrix (double)
 */
double determinant(const vector <vector <double>> &matrix, const int size);

#endif