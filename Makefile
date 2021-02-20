all: liteSH server

liteSH: bin/liteSH

bin/liteSH: build/main.o build/liteSH.o
	g++ -Wall -g build/main.o build/liteSH.o -I./home/evn/study/OS/liteSH/lib/about.so -ldl -o bin/liteSH

build/main.o: src/main.cpp
	g++ -Wall -c -g src/main.cpp -o  build/main.o

build/liteSH.o: src/liteSH.cpp
	g++ -Wall -c -g src/liteSH.cpp -o build/liteSH.o



server: bin/server

bin/server: build/server.o
	g++ -Wall -g build/server.o -o bin/server

build/server.o: src/server.cpp
	g++ -Wall -c -g src/server.cpp -o  build/server.o


clean:
	rm -rf build/*.o bin/liteSH bin/server