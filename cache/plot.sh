#!/bin/bash

gnuplot <<- EOF
set xlabel "memory access stride"
set ylabel "avg. access time"
set term png size 1000, 1000
set datafile separator ','

# Create some linestyles for our data
# pt = point type (triangles, circles, squares, etc.)
# ps = point size
set style line 1 lt 1 lc rgb "#A00000" lw 1 pt 7 ps 1
set style line 2 lt 1 lc rgb "#00A000" lw 1 pt 11 ps 1
set style line 3 lt 1 lc rgb "#5060D0" lw 1 pt 9 ps 1
set style line 4 lt 1 lc rgb "#0000A0" lw 1 pt 8 ps 1
set style line 5 lt 1 lc rgb "#D0D000" lw 1 pt 13 ps 1
set style line 6 lt 1 lc rgb "#00D0D0" lw 1 pt 12 ps 1
set style line 7 lt 1 lc rgb "#B200B2" lw 1 pt 5 ps 1
set style line 8 lt 1 lc rgb "#00A000" lw 1 pt 1 ps 1
set style line 9 lt 1 lc rgb "#5060D0" lw 1 pt 2 ps 1
set style line 10 lt 1 lc rgb "#0000A0" lw 1 pt 3 ps 1
set style line 11 lt 1 lc rgb "#D0D000" lw 1 pt 4 ps 1
set style line 12 lt 1 lc rgb "#00D0D0" lw 1 pt 6 ps 1
set style line 13 lt 1 lc rgb "#B200B2" lw 1 pt 10 ps 1
set style line 14 lt 1 lc rgb "#00A000" lw 1 pt 14 ps 1

set output "my_plot.png"
plot "data.csv" u 2:xtic(1) w lp ls 1 t "2KB Mem", \
"data.csv" u 3:xtic(1) w lp ls 2 t "4KB Mem", \
"data.csv" u 4:xtic(1) w lp ls 3 t "8KB Mem", \
"data.csv" u 5:xtic(1) w lp ls 4 t "16KB Mem", \
"data.csv" u 6:xtic(1) w lp ls 5 t "32KB Mem", \
"data.csv" u 7:xtic(1) w lp ls 6 t "64KB Mem", \
"data.csv" u 8:xtic(1) w lp ls 7 t "128KB Mem", \
"data.csv" u 9:xtic(1) w lp ls 8 t "256KB Mem", \
"data.csv" u 10:xtic(1) w lp ls 9 t "512KB Mem", \
"data.csv" u 11:xtic(1) w lp ls 10 t "1MB Mem", \
"data.csv" u 12:xtic(1) w lp ls 11 t "2MB Mem", \
"data.csv" u 13:xtic(1) w lp ls 12 t "4MB Mem", \
"data.csv" u 14:xtic(1) w lp ls 13 t "8MB Mem", \
"data.csv" u 15:xtic(1) w lp ls 14 t "16MB Mem"

EOF

#display "my_plot.png"

#./cache > data.csv
