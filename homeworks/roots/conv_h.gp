set terminal pngcairo size 800,600
set output "conv_h.png"

set title "Convergence vs step size"
set xlabel "h"
set ylabel "|E + 0.5|"

set logscale xy
set grid

plot "conv_h.txt" using 1:2 with linespoints lw 2 title "error"