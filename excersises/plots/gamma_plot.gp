set terminal png size 1000,700
set output "gamma_plot.png"

set title "Gamma Function"
set xlabel "x"
set ylabel "Gamma(x)"

set grid

plot "gamma_data.txt" using 1:2 with lines title "Gamma(x)"