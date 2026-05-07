set terminal png size 1000,700
set output 'damped.png'

set title 'Damped Oscillator'
set xlabel 't'
set ylabel 'u(t)'

plot \
'damped_data.txt' using 1:2 with lines lw 2 title 'Numerical', \
'damped_data.txt' using 1:3 with lines lw 2 title 'Exact'