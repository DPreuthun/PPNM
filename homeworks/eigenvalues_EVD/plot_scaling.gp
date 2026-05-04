set terminal pdf
set output "scaling.pdf"

set xlabel "Matrix size n"
set ylabel "Time (seconds)"
set title "Jacobi diagonalization scaling"

f(x) = a*x**3
fit f(x) "scaling.dat" using 1:2 via a

plot "scaling.dat" using 1:2 with points title "Measured time", \
     f(x) with lines title "a*n^3"