set term pdfcairo enhanced color font "Arial,10" size 8cm,6cm

set output "linearinterp.pdf"
set title "Linear spline interpolation"
set grid
plot "interp.dat" with lines title "spline", \
     "data.dat" with points pt 1 title "data"

set output "linearintegral.pdf"
set title "Integral of spline vs exact"
set grid
plot "integ.dat" using 1:2 with lines title "spline integral", \
     "integ.dat" using 1:3 with lines title "sin(x)"

set output