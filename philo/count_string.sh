#!/bin/bash

# Check if correct number of arguments provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 <string> <file>"
    exit 1
fi

string="$1"
file="$2"

# Check if file exists
if [ ! -f "$file" ]; then
    echo "Error: File '$file' not found"
    exit 1
fi

# Count occurrences using grep
count=$(grep -o "$string" "$file" | wc -l)

echo "The string '$string' appears $count times in '$file'"