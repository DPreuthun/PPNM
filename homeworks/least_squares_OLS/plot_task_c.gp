set terminal pngcairo size 900,600
set output "fit_taskC_variations.png"

set title "Task C: Parameter Variation Fits"
set xlabel "Time (days)"
set ylabel "Activity"

set grid
set key top right

plot \
    "data.txt" using 1:2:3 with yerrorbars title "Data", \
    "fit_variations.txt" using 1:2 with lines lw 2 title "Best fit", \
    "fit_variations.txt" using 1:3 with lines dt 2 title "ln(a) + sigma", \
    "fit_variations.txt" using 1:4 with lines dt 2 title "ln(a) - sigma", \
    "fit_variations.txt" using 1:5 with lines dt 3 title "lambda + sigma", \
    "fit_variations.txt" using 1:6 with lines dt 3 title "lambda - sigma"