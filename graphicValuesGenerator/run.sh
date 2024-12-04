#!/bin/bash

# Compile the necessary programs
g++ -std=c++11 -O3 -Wall gerador.cpp -lm -g -o gerador

# Navigate to the project directory

g++ -std=c++11 -O3 -Wall projeto.cpp -lm -g -o projeto

[ -f output.txt ] && rm output.txt

# Run the gerador executable 50 times with random n and m values and save the output to .in files
for i in $(seq 1 50); do
    n=$((1 + RANDOM % 100))          # Random n between 1 and 100
    m=$((100 + RANDOM % 901))        # Random m between 100 and 1000
    
    # Ensure growth with each iteration
    n=$((n * i / 50 + 1))
    m=$((m * i / 50 + 100))
    
    # Run the generator and save output
    ./gerador $n $m > "input_${i}.in"
done

# Process files 1 to 50
for i in $(seq 1 50); do
    input_file="input_${i}.in"
    base_name=$(basename "$input_file" .in)
    
    # Run the program with the input file
    echo "Input file: ${base_name}:" >> output.txt
    read n m < "$input_file"
    result=$((n * n * m * m * m))
    echo "Value n: $n" >> output.txt
    echo "Value m: $m" >> output.txt
    echo "Complexity Value: O($result)" >> output.txt
    # Capture time taken by the program and redirect output
    ./projeto < "$input_file" >> output.txt
    echo "" >> output.txt
done

for input_file in *.in; do
    rm "$input_file"
done

./linear_regression