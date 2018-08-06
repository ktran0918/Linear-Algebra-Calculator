/** Filename: matrix.cpp
 * Description: Library definition for useful matrix methods and linear algebra operations
 * Author: Khoa Tran
 */

#include "matrix.hpp"

/** Function: printMatrix
 * Description: print matrix in the following format:
 * 1 | 2 | 3
 * 4 | 5 | 6
 * 7 | 8 | 9
 * Input: 2D vector representing a matrix (passed by constant reference)
 * Output: none
 */

void printMatrix(const vector <vector <double>> &matrix) {
    // get dimensions
    int height = matrix.size();
    int width = matrix[0].size();

    // nested for loop to print the 2D matrix
    for (int i = 0; i < height; i++) {
        cout << '\t';
        for (int j = 0; j < width; j++) {
            cout << matrix[i][j];
            if (j != width - 1) {
                cout << "\t|\t";
            }
        }

        cout << endl;
    }
}

/** Helper function: coFactor
 * Description: factor a larger matrix (size n) and copy into a submatrix (of size n-1) for calculation of the determinant
 * Input: 2D vector representing a matrix (passed by constant reference), 2D vector representing a submatrix (passed by constant reference), row and column of the coefficient (ints), size of larger matrix (int)
 * Change: copy factored values from the larger matrix into the submatrix
 * Output: none
 */

void cofactor(const vector <vector<double>> &matrix, vector <vector<double>> &submatrix, int row, int col, int size) {
    int k = 0, l = 0; // row and column iterators for the submatrix
    
    // nest for loop to iterate through the larger matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // copy into the submatrix all values except on the same row and column as the coefficient
            if (i != row && j != col) {
                // copy by column ...
                submatrix[k][l] = matrix[i][j];
                l++;
                // then move to next row (when l reaches the column limit, reset to 0)
                if (l == size - 1) {
                    l = 0;
                    k++;
                }
            }
        }
    }

    // print submatrix to check
    /*cout << "Begin printing submatrix:\n";
    for (k = 0; k < submatrix.size(); k++) {
        for (l = 0; l < submatrix.size(); l++) {
            cout << submatrix[k][l] << ' ';
        }
        cout << endl;
    }*/    
}

/** Function: determinant
 * Description: calculate the determinant of a matrix
 * - Recursive function: in each recursion, a submatrix is factored out of the larger matrix, until the smallest submatrix is obtained (size 1), where the determinant is the sole element. Each cofactor is multiplied by a coefficient (positive or negative according to the column) and added to the determinant.
 * Input: 2D vector representing a matrix (passed by constant reference), size of the matrix (int)
 * TODO: it's not crucial, but would be efficient to search for the best row or column to start the factoring process. Ideally, the method would first find the row or column with the most 0's or 1's, instead of always starting factoring from the first row.
 * Output: the determinant (double)
 */

double determinant(const vector <vector <double>> &matrix, int size) {
    double det = 0; // determinant value to be returned

    // base case, when matrix is size 1
    if (size == 1) {
        return matrix[0][0];
    }

    // submatrix (cofactor)
    vector <vector <double>> submatrix(size, vector <double> (size));

    int sign = 1; // sign to alternate by coefficients

    // loop through the first row of the matrix
    for (int i = 0; i < size; i++) {
        // obtain cofactor
        cofactor(matrix, submatrix, 0, i, size);
        // add to the determinant the result of +/- coefficient times the determinant of the cofactor
        det += (sign * matrix[0][i]) * determinant(submatrix, size - 1);

        // switch sign by column
        sign = -sign;
    }

    return det;
}