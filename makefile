kill_game: main.c
	gcc main.c `pkg-config --cflags --libs sdl2` -o kill_game
