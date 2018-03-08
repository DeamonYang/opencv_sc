udp.o:udp.c udp.h
	gcc -c udp.c

main.o:main.cpp
	g++ -c main.cpp #`pkg-config --cflags --libs opencv`

main:udp.o main.o
	g++ -o main main.o udp.o `pkg-config --cflags --libs opencv`

clean:
	rm *.o main
