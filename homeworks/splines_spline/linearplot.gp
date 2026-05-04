set terminal pngcairo size 800,600 enhanced font "Arial,10"

# -------- Linear interpolation --------
set output "linearinterp.png"
set title "Linear spline interpolation"
set xlabel "x"
set ylabel "y"
set grid

plot "interp.dat" using 1:2 with lines lw 2 title "spline", \
     "data.dat" using 1:2 with points pt 7 ps 1 title "data", \
     cos(x) with lines dt 2 title "cos(x)"

# -------- Integral comparison --------
set output "linearintegral.png"
set title "Integral of spline vs exact"
set xlabel "x"
set ylabel "Integral"
set grid

plot "integ.dat" using 1:2 with lines lw 2 title "spline integral", \
     "integ.dat" using 1:3 with lines dt 2 title "sin(x)"

set output