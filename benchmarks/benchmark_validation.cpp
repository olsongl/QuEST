#include <iostream>
#include <chrono>
#include "quest/src/core/utilities.hpp" // Include your utility functions
#include "quest/include/types.h"       // Include necessary types

using namespace std;
using namespace chrono;

// Helper function to measure execution time
template <typename Func>
double measureExecutionTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

// Benchmarking function
void benchmarkValidationFunctions(int numQubits) {
    cout << "Benchmarking for " << numQubits << " qubits:" << endl;

    // Create test matrices
    qindex dim = 1ULL << numQubits; // 2^numQubits
    vector<int> matrix(dim * dim, 1); // Example matrix (filled with 1s)

    // Wrap the matrix in a struct (e.g., DiagMatr)
    DiagMatr diagMatr = {numQubits, dim, matrix.data(), nullptr, nullptr, nullptr, nullptr};

    // Benchmark util_isUnitary
    double unitaryTime = measureExecutionTime([&]() {
        util_isUnitary(diagMatr, 1e-6);
    });
    cout << "  util_isUnitary: " << unitaryTime << " ms" << endl;

    // Benchmark util_isHermitian
    // double hermitianTime = measureExecutionTime([&]() {
    //     util_isHermitian(diagMatr, 1e-6);
    // });
    // cout << "  util_isHermitian: " << hermitianTime << " ms" << endl;

    // Add benchmarks for other validation functions as needed
}

int main() {
    // Test for various numbers of qubits
    for (int numQubits = 5; numQubits <= 16; numQubits++) {
        benchmarkValidationFunctions(numQubits);
    }
    return 0;
}