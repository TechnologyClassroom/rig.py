#!/bin/bash

# Start with bash run-rtog-loop.sh

echo "Close with CTRL+C keystroke"

# Output a new name every second.
while true; do
  python3 rtog.py \
    | head -n 1 \
    | awk -F',' '{print $2 " " $1}' \
    | sed 's/^ //'
  sleep 1
done

# Explaination
# while true; do command; done # Infinite loop. Close with CTRL+c keystroke.
# head -n 1 # Output the first line
# awk -F',' '{print $2 " " $1}' # If there is a comma, print the second half first.
# sed 's/^ //' # Remove leading space caused by awk.
