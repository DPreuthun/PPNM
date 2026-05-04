set terminal pngcairo size 800,600
set output "stratified_plot.png"

set logscale xy
set xlabel "N"
set ylabel "Error"
set grid
set key left top

plot \
"stratified.txt" using 1:2 with linespoints title "Plain MC", \
"stratified.txt" using 1:3 with linespoints title "Stratified", \
1/sqrt(x) with lines title "N^{-1/2}"