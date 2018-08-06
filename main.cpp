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
 * Description: provides main program logic
 * TODO: implement command line arguments (see README for details)
 * Input: none
 * Output: 0 (int)
 */

int main() {
    displayInstructions();

    vector <vector <double>> matrixA;
    getMatrixFromUser(matrixA);

    int height = matrixA.size();
    int width = matrixA[0].size();

    cout << "Size: " << height << " x " << width << "\n\n";

    printMatrix(matrixA);

    cout << endl;

    cout << "Determinant: " << determinant(matrixA, height) << "\n\n";

    return 0;
}