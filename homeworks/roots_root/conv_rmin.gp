set terminal pngcairo size 800,600
set output "conv_rmin.png"

set title "Convergence vs rmin"
set xlabel "rmin"
set ylabel "|E + 0.5|"

set logscale x
set grid

plot "conv_rmin.txt" using 1:2 with linespoints lw 2 title "error"