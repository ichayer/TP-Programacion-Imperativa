COMPILER=gcc
OUTPUT_FILE_BUE= arbolesADTBUE
OUTPUT_FILE_VAN= arbolesADTVAN
CFLAGS= -Wall -pedantic -std=c99 -fsanitize=address -g -lm
FILES= cityADT.c CSV.c main.c

all: arbolesADTBUE arbolesADTVAN

arbolesADTBUE:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT_FILE_BUE) $(FILES) -D SPNAME=8 -D NEIGH=3

arbolesADTVAN:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT_FILE_VAN) $(FILES) -D SPNAME=7 -D NEIGH=13

clean:
	rm -fr $(OUTPUT_FILE_BUE) $(OUTPUT_FILE_VAN) *.o
