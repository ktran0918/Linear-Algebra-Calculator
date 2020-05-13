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
 * Description: print matrix in the following format:
 * 1    |   2   |   3
 * 4    |   5   |   6
 * 7    |   8   |   9
 * Input: 2D vector representing a matrix (passed by constant reference)
 * Output: none
 */
void printMatrix(const vector <vector <double>> &matrix);

/** Function: matrixIsSquare
 * Description: compare a matrix's height and width to determine squareness
 * Input: matrix (2D vector) (constant reference)
 * Output: bool
 */
bool matrixIsSquare(const vector <vector <double>> &matrix);

/** Function: determinant
 * Description: calculate the determinant of a matrix
 * - Recursive function: in each recursion, a submatrix is factored out of the larger matrix, until the smallest submatrix is obtained (size 1), where the determinant is the sole element. Each cofactor is multiplied by a coefficient (positive or negative according to the column) and added to the determinant.
 * Input: 2D vector representing a matrix (passed by constant reference), size of the matrix (int)
 * TODO: it's not crucial, but would be efficient to search for the best row or column to start the factoring process. Ideally, the method would first find the row or column with the most 0's or 1's, instead of always starting factoring from the first row.
 * Output: the determinant (double)
 */
double determinant(const vector <vector <double>> &matrix, const int size);

/** Function: rref
 * Description: calculate a matrix's row-reduced echelon form
 * 
 */
vector <vector<double>> rref(vector <vector <double>> matrix);

#endif