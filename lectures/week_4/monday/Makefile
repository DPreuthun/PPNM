CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm

fig2.png: erf.data Makefile
	echo '\
	set terminal png ;\
	set output "$@" ;\
	set tics out ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	plot [][] \ 
		"$<" index 1 using 1:2 with linespoints ;\
		"$<" index 1 using 1:3 with lines ;\
		' | tee log.fig2.gpi | gnuplot

fig1.svg: fig1.gpi erf.data
	gnuplot $<

erf.data: main Makefile
	./$< -xmin -2 -xmax 2 -dx 0.5 > $@ 2>log.erf
	echo "\n\n" >> $@
	./$< -xmin 0 -xmax 10 -dx 0.5 >> $@ 2>>log.erf