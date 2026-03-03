CXXFLAGS += -std=c++23 -Wall -O
LDLIBS += -lstdc++ -lm -lpthread

times.svg: out.times Makefile
	echo '\
			set terminal svg ;\
			set output "$@" ;\
			set object 1 rectangle from screen 0,0 to screen 1,1 behind fillcolor rgb "white" fillstyle solid 1.0 noborder ;\
			set xlabel "number of threads" ;\
			set ylabel "real time" ;\
			a = 1; b = 10 ;\
			f(x)=a+b/x ;\
			fit f(x) "$<" using 1:2 via a,b ;\
			plot \
				"$<" using 1:2 with linespoints title "times", \
				f(x) title "fit with 1/n" ;\
			' | tee log.times | gnuplot

TIME = /usr/bin/time -f "$$nthreads %e" -a -o $@
N = 1e9

out.times : main Makefile
	>$@
	>log.main
	for nthreads in 1 2 3 4 5 6 7 8 9 10; do \
		$(TIME) ./main -nthreads $$nthreads -nterms $(N) >>log.main ;\
	done