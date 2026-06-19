set terminal pngcairo size 1000,700
set output "higgs_fit.png"

set title "Higgs Boson Breit-Wigner Fit"
set xlabel "Energy (GeV)"
set ylabel "Signal"

set grid

set key top right

plot \
    "data.dat" using 1:2:3 with yerrorbars title "Experimental Data", \
    "fit.dat" using 1:2 with lines linewidth 2 title "Breit-Wigner Fit"