set terminal png size 1000,700
set output "lngamma_plot.png"

set title "Log Gamma Function"
set xlabel "x"
set ylabel "ln(Gamma(x))"

set grid

plot "lngamma_data.txt" using 1:2 with lines title "lnGamma(x)"