set terminal png size 1000,1000
set output 'threebody.png'

set title 'Three-body Figure-8 Orbit'

set size square

plot \
'threebody.txt' using 1:2 with lines lw 2 title 'body 1', \
'threebody.txt' using 3:4 with lines lw 2 title 'body 2', \
'threebody.txt' using 5:6 with lines lw 2 title 'body 3'