all: sorter

sorter: scannerCSVsorter.c mergesort.c
    gcc -c scannerCSVsorter.c
    gcc -c mergesort.c
    gcc -Wall -Werror -fsanitize=address -o sorter scannerCSVsorter.o mergesort.o

clean:
    rm -rf sorter
