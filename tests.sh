#!/bin/bash

# filepath: /scratch/lawsonde/omp/QuEST/benchmarks/run_benchmarks.sh

# Output CSV file
output_csv="benchmark_results.csv"

# Thread counts to test
threads=(1 2 4 8 16 32)

# Qubit range
min_qubits=5
max_qubits=16

# Initialize the CSV file
echo "Threads,Qubits,util_isUnitary (ms)" > $output_csv

# Run benchmarks for each thread count
for t in "${threads[@]}"; do
    echo "Running benchmarks with $t threads..."
    
    # Set the number of threads for OpenMP
    export OMP_NUM_THREADS=$t

    # Temporary file to store raw results
    temp_file="temp_results.txt"
    srun ./benchmark_validation > $temp_file

    # Parse the results and average them
    for ((q=$min_qubits; q<=$max_qubits; q++)); do
        # Extract the util_isUnitary time for the current qubit count
        times=$(grep "Benchmarking for $q qubits:" -A 1 $temp_file | grep "util_isUnitary" | awk '{print $2}')
        
        # Calculate the average (if multiple runs are needed, modify this section)
        avg_time=$(echo "$times" | awk '{sum+=$1} END {if (NR > 0) print sum/NR; else print 0}')
        
        # Append the result to the CSV
        echo "$t,$q,$avg_time" >> $output_csv
    done
done

# Clean up
rm -f temp_results.txt

echo "Benchmarking complete. Results saved to $output_csv."