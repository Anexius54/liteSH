about.so: about.o
	g++ -Wall -g -shared -o about.so about.o

about.o: about.cpp
	g++ -c -fPIC about.cpp

clean:
	rm -rf *.o *.so