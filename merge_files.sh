#!/bin/bash

# Name of the output file
output_file="merged.cpp"

# Clear the output file if it exists
> $output_file

# Find all .h and .cpp files in the current directory
for file in *.h *.cpp; do
    if [[ -f $file ]]; then
        echo "// Contents of $file" >> $output_file  # Add a comment to indicate the source file
        cat "$file" >> $output_file  # Append the contents of the file to the output
        echo -e "\n" >> $output_file  # Add a newline between files
    fi
done

echo "All files merged into $output_file"
