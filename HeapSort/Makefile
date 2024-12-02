all:
	g++ test.cpp -o test -std=c++20 -O2

report:
	xelatex report.tex

clean:
	rm -f List *.o *.aux *.log *.out report.pdf

.PHONY: all report clean