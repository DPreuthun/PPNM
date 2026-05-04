set terminal pngcairo size 800,600
set output "wave.png"

set title "Hydrogen ground state wavefunction"
set xlabel "r"
set ylabel "f(r)"
set grid

plot "wave.txt" using 1:2 with lines lw 2 title "numerical", \
     "wave.txt" using 1:3 with lines lw 2 title "exact"