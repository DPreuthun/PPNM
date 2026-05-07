set terminal png size 1000,1000
set output 'precession.png'

set title 'Relativistic Precession'
set size square

plot 'orbit_precession.txt' using 1:2 \
with lines lw 2 title 'precession'