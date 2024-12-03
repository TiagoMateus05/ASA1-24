#!/bin/bash

# Navigate to the project directory
cd ..

# Compile the program
g++ -std=c++11 -O3 -Wall projeto.cpp -lm -g -o projeto

# Navigate back to the test directory
cd test

# Create the diff directory if it doesn't exist
mkdir -p diff

# Loop through all input files
for input_file in *.in; do
    # Extract the base name of the file (without extension)
    base_name=$(basename "$input_file" .in)

    # Run the program with the input file and capture the output and time
    { time ../projeto < "$input_file" > "${base_name}.temp"; } 2> "${base_name}.time"

    # Compare the actual output with the expected output
    diff -u "${base_name}.temp" "${base_name}.out" > "diff/${base_name}.diff"
    rm "${base_name}.temp"

    # Check if there are differences
    if [ -s "diff/${base_name}.diff" ]; then
        echo "Test ${base_name} failed. Differences found:"
        cat "diff/${base_name}.diff"
    else
        echo "Test ${base_name} passed. No differences found."
        rm "diff/${base_name}.diff"
    fi

    # Output the time taken
    echo "Time taken for ${base_name}:"
    cat "${base_name}.time"
    rm "${base_name}.time"
done