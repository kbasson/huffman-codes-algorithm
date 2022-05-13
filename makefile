huffman: huffman.o helpers.o
	clang -Wall -pedantic -std=c99 huffman.o helpers.o -o huffman

huffman.o: huffman.c huffman.h
	clang -Wall -pedantic -std=c99 -c huffman.c -o huffman.o

helpers.o: helpers.c huffman.h
	clang -Wall -pedantic -std=c99 -c helpers.c -o helpers.o

clean:
	rm *.o
