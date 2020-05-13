/** Filename: matrix.cpp
 * Description: Library definition for useful matrix methods and linear algebra operations
 * Author: Khoa Tran
 */

#include "matrix.hpp"

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

    cout << endl;
}

void fixNegativeZero(vector <vector <double>> &matrix) {
    // get dimensions
    int height = matrix.size();
    int width = matrix[0].size();

    // nested for loop to access every element of the matrix
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] == 0.0) {
                matrix[i][j] = 0;
            }
        }
    }
}

bool matrixIsSquare(const vector <vector <double>> &matrix) {
    return matrix.size() == matrix[0].size();
}

/** Helper function: cofactor
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

vector <vector<double>> rref(vector <vector <double>> matrix) {
    int height = matrix.size();
    int width = matrix[0].size();
    int lead = 0;

    while (lead < height) {
        double divisor, multiplier;

        for (int r = 0; r < height; r++) { // for each row ...
            /* calculate divisor and multiplier */
            divisor = matrix[lead][lead];
            multiplier = matrix[r][lead] / matrix[lead][lead];

            for (int c = 0; c < width; c++) { // for each column ...
                if (r == lead)
                    matrix[r][c] /= divisor;               // make pivot = 1
                else
                    matrix[r][c] -= matrix[lead][c] * multiplier;  // make other = 0
            }
        }

        lead++;
    }

    fixNegativeZero(matrix);

    return matrix;
}