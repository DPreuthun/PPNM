set terminal pngcairo size 800,600
set output "error_plot.png"

set logscale xy
set xlabel "N"
set ylabel "Error"
set grid
set key left top

# --- CHOOSE ONE DATASET (0=circle, 1=gaussian, 2=ellipsoid)
i = 0   # <-- change this to 1 or 2 if needed

# Reference scaling
c = 1.0

plot \
"out.txt" index i using 1:3 with linespoints title "Estimated error", \
"out.txt" index i using 1:4 with linespoints title "Actual error", \
c/sqrt(x) with lines title "1/sqrt(N)"