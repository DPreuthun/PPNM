set terminal png size 1000,1000
set output 'circle.png'

set title 'Newtonian Circular Orbit'
set size square

plot 'orbit_circle.txt' using 1:2 \
with lines lw 2 title 'circle'