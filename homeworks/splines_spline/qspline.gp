set terminal pngcairo size 800,600 enhanced font "Arial,10"
set grid

# ================= CONSTANT =================
set output "qspline_const.png"
set title "Quadratic spline: y = 1"
set xlabel "x"
set ylabel "y"
set xrange [1:5]
set yrange [0.9:1.1]

plot "const.dat" using 1:2 with lines lw 2 title "spline", \
     "const_pts.dat" using 1:2 with points pt 7 ps 1 title "data"

# ================= LINEAR =================
set output "qspline_linear.png"
set title "Quadratic spline: y = x"
set xlabel "x"
set ylabel "y"
set xrange [1:5]
set yrange [1:5]

plot "linear.dat" using 1:2 with lines lw 2 title "spline", \
     "linear_pts.dat" using 1:2 with points pt 7 ps 1 title "data", \
     x with lines dt 2 title "exact"

# ================= QUADRATIC =================
set output "qspline_quad.png"
set title "Quadratic spline: y = x^2"
set xlabel "x"
set ylabel "y"
set xrange [1:5]
set yrange [1:25]

plot "quad.dat" using 1:2 with lines lw 2 title "spline", \
     "quad_pts.dat" using 1:2 with points pt 7 ps 1 title "data", \
     x*x with lines dt 2 title "exact"

# ================= QUADRATIC INTEGRAL =================
set output "qspline_quad_integral.png"
set title "Integral check: y = x^2"
set xlabel "x"
set ylabel "Integral"
set xrange [1:5]
set yrange [0:50]

plot "quad.dat" using 1:4 with lines lw 2 title "spline integral", \
     x**3/3 with lines dt 2 title "exact"

set output