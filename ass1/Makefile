all: scannerCSVsorter.c mergesort.o
	gcc scannerCSVsorter.c mergesort.o -o sorter
mergesort.o: mergesort.c
	gcc -c mergesort.c -o mergesort.o
clean:
	rm -rf sorter mergesort.o
