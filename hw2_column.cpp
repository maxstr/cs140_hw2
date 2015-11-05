#include <iostream>
#include <omp.h>
#include <cstdlib>

// Sets the matrix dimensions

int main(int argc, char* argv[]) {
    int numThreads = strtof(argv[1], NULL);
    const int n = strtof(argv[2], NULL);
    double A[n][n];
    double x[n];
    double b[n];
    if (argc != 3) {
        std::cout << "Proper usage ./prog numThreads matrixSize" << std::endl;
        return 1;
    }
        // Generate a random NxN triangular matrix as well as a Nx1 column vector.
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = i; j < n; j++) {
            A[i][j] = rand() % 8 + 1;
            sum += A[i][j];
        } 
        for (int j = 0; j < i; j++)
            A[i][j] = 0;
        b[i] = sum;
    }
    std::cout << "Printing the matrix" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { 
            std::cout << A[i][j] << " ";
        }
        std::cout << ": " << b[i] << std::endl;
    }
    for (int i = 0; i < n; i++) {
        x[i] = b[i];
    }
    
    
    for (int i = n-1; i >= 0; i--) {
        x[i] /= A[i][i];
#pragma omp parallel for num_threads(numThreads) 
        for (int j = 0; j < i; j++) {
            x[j] -= (A[j][i] * x[i]);
        }
    }
    
    for (int i = 0; i < n; i++)
        std::cout << "x" << i << " : " << x[i] << std::endl;


    return 0;
}



