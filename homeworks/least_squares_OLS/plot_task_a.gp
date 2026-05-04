# Output
set terminal pngcairo size 800,600
set output "fit_taskA.png"

# Labels
set title "Radioactive Decay Fit (Task A)"
set xlabel "Time (days)"
set ylabel "Activity"

# Grid
set grid

# Legend
set key top right

# Plot:
# using: x:y:dy:errorbars and fitted curve
plot \
    "data.txt" using 1:2:3 with yerrorbars title "Data", \
    "data.txt" using 1:4 with lines lw 2 title "Fit"