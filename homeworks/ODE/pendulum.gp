set terminal png size 1000,700
set output 'pendulum.png'

set title 'Pendulum with Friction'
set xlabel 't'
set ylabel 'theta(t)'

plot \
'pendulum_data.txt' using 1:2 with lines lw 2 title 'Numerical', \
'pendulum_data.txt' using 1:3 with lines lw 2 title 'Approximate Exact'