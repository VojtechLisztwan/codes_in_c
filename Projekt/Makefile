pacman: main.c
	gcc main.c -o pacman -g -Wall $(shell pkg-config --cflags --libs sdl2 SDL2_image SDL2_ttf) -lm

run: pacman
	./pacman

build: pacman
	make pacman
	make run

clean:
	rm pacman