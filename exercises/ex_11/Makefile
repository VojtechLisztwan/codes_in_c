TARGET=main
all:$(TARGET)


$(TARGET): main.o array.o
	gcc main.o array.o -o main
	gcc $^ -o $(TARGET)

main.o: main.c
	gcc -c main.c -o main.o

array.o: array.c
	gcc -c array.c -o array.o

clean: 
	-rm main
	-rm *.o

build:
	make clean
	make
	./$(TARGET)