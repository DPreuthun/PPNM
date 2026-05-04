set terminal pdf
set output "wavefunctions.pdf"

set xlabel "r"
set ylabel "f(r)"
set title "Hydrogen s-wave radial eigenfunctions"

plot "wavefunctions.dat" using 1:2 with lines lw 2 title "k=1 (1s)", \
     "wavefunctions.dat" using 1:3 with lines lw 2 title "k=2 (2s)", \
     "wavefunctions.dat" using 1:4 with lines lw 2 title "k=3 (3s)"