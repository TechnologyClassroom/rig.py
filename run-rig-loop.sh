#!/bin/bash

# Start with bash run-rig-loop.sh

echo "Close with CTRL+C keystroke"

# Output a new name every second.
while true; do
  python3 rig.py \
    | head -n 1
  sleep 1
done

# Explaination
# while true; do command; done # Infinite loop. Close with CTRL+c keystroke.
# head -n 1 # Output the first line
