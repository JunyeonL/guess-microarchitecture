#!/bin/bash


echo "===================================="
echo "Start to measuring store buffer size"
echo "===================================="

echo "Step1. Create Instruction sequences and execute (1 ~ 70 instructions)"
echo " -- create data.txt to record result output"

./cache > data.txt

echo "Step2. Start to draw plot"
sleep 1

gnuplot <<- EOF
set xlabel "store buffer entries"
set ylabel "time"
set xtics 0, 5, 70
set term png
set output "my_plot.png"
#plot 'data.txt' u 1:2 with l, 'data.txt' u 1:3 with l, 'data.txt' u 1:4 with l
plot 'data.txt' u 1:2 with l

EOF

display "my_plot.png" &

cat data.txt

#./cache > data.csv


echo "End"
