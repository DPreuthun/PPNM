set terminal pngcairo size 800,600
set output "error_plot.png"

set title "Error vs Requested Accuracy for erf(1)"
set xlabel "acc"
set ylabel "|error|"

set logscale x
set logscale y

set grid

plot "out.txt" using 1:2 with linespoints title "|erf(1) - exact|"