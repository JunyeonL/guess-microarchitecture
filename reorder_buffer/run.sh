#!/bin/bash

echo "======================================"
echo "Start to measuring reorder buffer size"
echo "======================================"

echo "Step1. Create Instruction sequences and execute (80 ~ 250 instructions)"
echo " -- create output.csv to record result output"

./reorder > output.csv

sleep 1
echo "Step2. Start Draw a graph (x-axis : reorder buffer, y-axis : execution time)"

gnuplot <<- EOF
set xlabel "reorder buffer entries"
set ylabel "time"
set xtics 80, 20, 300
set term png
set output "my_plot.png"
#plot 'data.txt' u 1:2 with l, 'data.txt' u 1:3 with l, 'data.txt' u 1:4 with l
plot 'output.csv' u 1:2 with l

EOF

sleep 1
display "my_plot.png" &

cat output.csv

echo "End"

