set terminal pdf
set output "dr_convergence.pdf"

set xlabel "Δr"
set ylabel "Ground state energy"
set title "Convergence of ground state energy vs Δr"

plot "dr_convergence.dat" using 1:2 with linespoints lw 2 title "Numerical", \
     -0.5 with lines title "Exact"