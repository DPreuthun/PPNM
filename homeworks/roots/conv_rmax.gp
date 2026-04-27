set terminal pngcairo size 800,600
set output "conv_rmax.png"

set title "Convergence vs rmax"
set xlabel "rmax"
set ylabel "|E + 0.5|"
set grid

plot "conv_rmax.txt" using 1:2 with linespoints lw 2 title "error"