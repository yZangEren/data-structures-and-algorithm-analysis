all:
	g++ main.cpp -o BinarySearchTree -std=c++20 -O2

run: all
	./BinarySearchTree

report:
	xelatex report.tex

clean:
	rm -f BinarySearchTree *.o *.aux *.log *.out report.pdf

.PHONY: all run report clean