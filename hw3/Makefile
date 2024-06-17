all: wordrange

wordrange: wordrange.o
	g++ -o wordrange wordrange.o

wordrange.o: wordrange.cpp
	g++ -c wordrange.cpp

clean:
	rm -f *.o wordrange