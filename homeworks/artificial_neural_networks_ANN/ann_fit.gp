set terminal pngcairo size 1000,700

set output "ann_fit.png"

set title "Artificial Neural Network Approximation"

set xlabel "x"
set ylabel "y"

set grid

plot \
    "data.dat" using 1:2 with points pt 7 ps 1.5 title "Target function", \
    "fit.dat" using 1:2 with lines lw 2 title "ANN approximation"