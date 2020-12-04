COMPILER=gcc
OUTPUT_FILE_BUE= arbolesADTBUE
OUTPUT_FILE_VAN= arbolesADTVAN
CFLAGS= -Wall -pedantic -std=c99 -fsanitize=address -g -lm
FILES= cityADT.c CSV.c main.c

all: arbolesADTBUE arbolesADTVAN

arbolesADTBUE:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT_FILE_BUE) $(FILES) -D BUE

arbolesADTVAN:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT_FILE_VAN) $(FILES) -D VAN

clean:
	rm -fr $(OUTPUT_FILE_BUE) $(OUTPUT_FILE_VAN) *.dSYM *.o
