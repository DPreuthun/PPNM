set terminal pngcairo size 900,600
set output 'timing.png'
set grid
set key top left
set xlabel 'Matrix size N'
set ylabel 'Average runtime (s)'
set title 'Time scaling of Rayleigh quotient minimization'
set xtics 2000
set format y '%.2f'
plot 'timing.dat' using 1:2 with linespoints lw 2 pt 7 title 'Measured runtime'
