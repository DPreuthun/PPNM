set terminal pdf
set output "rmax_convergence.pdf"

set xlabel "rmax"
set ylabel "Ground state energy"
set title "Convergence of ground state energy vs rmax"

plot "rmax_convergence.dat" using 1:2 with linespoints lw 2 title "Numerical", \
     -0.5 with lines title "Exact"