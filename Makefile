all:
	g++ -std=c++11 -O3 -Wall *.cpp -lm -g
	./a.out

clean:
	rm a.out