all:
	gcc -c example_2.c `pkg-config --cflags gtk+-3.0` -o example.o
	gcc -c main.c -o main.o
	gcc main.o example.o `pkg-config --libs gtk+-3.0` -o main.out
	rm -rf *.o
	./main.out