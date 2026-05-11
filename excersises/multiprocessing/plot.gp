set terminal png size 1000,700
set output "plot.png"

set title "Runtime vs Number of Threads"
set xlabel "Threads"
set ylabel "Time (seconds)"

set grid

plot "times.txt" using 1:2 with linespoints