#!/bin/bash

echo "Start"

./cache > data.txt

gnuplot <<- EOF
set xlabel "dtlb entries"
set ylabel "time"
set xtics 0, 64, 1024
set term png
set output "my_plot.png"
plot 'data.txt' u 1:2 with l

EOF

display "my_plot.png" &

cat data.txt

echo "End"
