set terminal png size 1000,700
set output 'oscillator.png'

set title 'Harmonic Oscillator'
set xlabel 't'
set ylabel 'u(t)'

plot \
'oscillator_data.txt' using 1:2 with lines lw 2 title 'Numerical', \
'oscillator_data.txt' using 1:3 with lines lw 2 title 'Exact'