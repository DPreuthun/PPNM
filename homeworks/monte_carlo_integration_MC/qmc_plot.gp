set terminal pngcairo size 800,600
set output "qmc_plot.png"

set logscale xy
set xlabel "N"
set ylabel "Error"
set grid
set key left top

plot \
"qmc.txt" using 1:2 with linespoints title "LCG", \
"qmc.txt" using 1:3 with linespoints title "mt19937", \
"qmc.txt" using 1:4 with linespoints title "Halton (QMC)", \
1/sqrt(x) with lines title "MC ~ N^{-1/2}", \
1/x with lines title "QMC ~ N^{-1}"