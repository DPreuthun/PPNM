set terminal png size 1000,700
set output "erf_plot.png"

set title "Error Function erf(x)"
set xlabel "x"
set ylabel "erf(x)"

set grid

plot "erf_data.txt" using 1:2 with lines title "erf(x)"