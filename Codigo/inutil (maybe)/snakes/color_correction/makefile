all: color_correction

color_correction: color_correction.o matrix_tester.o
				gcc -Wall -ansi -g color_correction.o matrix_tester.o -o color_correction

color_correction.o: color_correction.c
				gcc -Wall -ansi -g -c color_correction.c matrix_tester.c 

clean: rm -rf *o color_correction
