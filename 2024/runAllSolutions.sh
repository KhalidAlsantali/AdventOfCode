#!/bin/bash

# Function to print separator line
print_separator() {
    printf '%*s\n' 50 '' | tr ' ' '-'
}

# Find all .exe files recursively, excluding ones with "interactive" in the name
while IFS= read -r -d '' exe_file; do
    echo "Executing: $(basename "$exe_file")"
    
    # Store original directory and change to exe's directory
    original_dir=$(pwd)
    exe_dir=$(dirname "$exe_file")
    cd "$exe_dir" || exit 1
    
    # Execute and time the command while capturing output
    {
        start_time=$(date +%s%N)
        output=$(wine "$(basename "$exe_file")" 2>&1)
        end_time=$(date +%s%N)
        
        # Calculate execution time in milliseconds
        execution_time=$(( (end_time - start_time) / 1000000 ))
        
        # Print output if there is any
        if [ -n "$output" ]; then
            echo "$output"
        fi
        
        # Print execution time with color
        if [ "$execution_time" -gt 1000 ]; then
            printf "\033[31mExecution time: %d ms\033[0m\n" "$execution_time"
        else
            printf "\033[32mExecution time: %d ms\033[0m\n" "$execution_time"
        fi
        
    } || {
        printf "\033[31mFailed to execute: %s\033[0m\n" "$(basename "$exe_file")"
        printf "\033[31m%s\033[0m\n" "$?"
    }
    
    # Return to original directory
    cd "$original_dir" || exit 1
    
    # Print separator
    print_separator
    
done < <(find . -type f -name "*.exe" ! -name "*interactive*" -print0)