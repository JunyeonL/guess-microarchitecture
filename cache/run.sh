#!/bin/bash

echo "======================================"
echo "Step0. Compile"
echo "======================================"

sleep 3
make

echo "==========================================================================="
echo "Step1. Allocate linear memory spaces"
echo "       and access each memory with different stride (it takes a few minute)"
echo "==========================================================================="

echo "   - Memory (from 2KB to 16MB) -"
echo "   - Stride (from 8B to 8MB)   -"
echo "   - If you want to print full log, please set CACHE_DEBUG to 1 in config.h"

sleep 3
./cache

echo "======================================"
echo "Step2. Start draw a graph"
echo "======================================"
echo "  - x-axis : size of allocated memory"
echo "  - y-axis : execution time"
echo "  - each-line : size of stride"
sleep 2

./plot.sh

echo "my_plot.png file is generated"

display "my_plot.png" &

echo "End"
