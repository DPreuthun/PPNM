set terminal png size 1000,1000
set output 'ellipse.png'

set title 'Newtonian Elliptical Orbit'
set size square

plot 'orbit_ellipse.txt' using 1:2 \
with lines lw 2 title 'ellipse'