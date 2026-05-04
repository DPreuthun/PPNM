set term pdfcairo enhanced color size 8cm,6cm
set grid

# ================= CONSTANT =================
set output "qspline_const.pdf"
set title "Quadratic spline: y = 1"
plot "const.dat" using 1:2 with lines title "spline", \
     "const_pts.dat" with points pt 7 title "data"

# ================= LINEAR =================
set output "qspline_linear.pdf"
set title "Quadratic spline: y = x"
plot "linear.dat" using 1:2 with lines title "spline", \
     "linear_pts.dat" with points pt 7 title "data", \
     x with lines title "exact"

# ================= QUADRATIC =================
set output "qspline_quad.pdf"
set title "Quadratic spline: y = x^2"
plot "quad.dat" using 1:2 with lines title "spline", \
     "quad_pts.dat" with points pt 7 title "data", \
     x*x with lines title "exact"

# ================= QUADRATIC INTEGRAL =================
set output "qspline_quad_integral.pdf"
set title "Integral check: y = x^2"
plot "quad.dat" using 1:4 with lines title "spline integral", \
     x**3/3 with lines title "exact"

set output