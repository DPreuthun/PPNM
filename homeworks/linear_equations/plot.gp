set terminal pdf
set output "qr_scaling.pdf"

set xlabel "N"
set ylabel "Time (seconds)"
set title "QR Factorization Scaling"

f(x) = a*x**3
fit f(x) 'out.times.data' using 1:2 via a

plot 'out.times.data' using 1:2 with points title "Measured time", \
     f(x) with lines title "a*N^3"

set output