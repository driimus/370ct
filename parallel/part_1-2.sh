#!/bin/bash

# This script runs the code for Task 2 with different scheduling types.
./part_1-2 OMP_SCHEDULE="auto"
./part_1-2 OMP_SCHEDULE="dynamic"
./part_1-2 OMP_SCHEDULE="guided,4"
