FLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -Iinclude

all: bin/tp2.out

all_windows: bin/tp2.exe

bin/tp2.exe: obj/main.o obj/Wall.o | bin
	g++ $(FLAGS) obj/main.o obj/Wall.o -o bin/tp2.exe

bin/tp2.out: obj/main.o obj/Wall.o | bin
	g++ $(FLAGS) obj/main.o obj/Wall.o -o bin/tp2.out

obj/main.o: src/main.cpp include/Wall.hpp | obj
	g++ $(FLAGS) -c src/main.cpp -o obj/main.o

obj/Wall.o: src/Wall.cpp include/Wall.hpp | obj
	g++ $(FLAGS) -c src/Wall.cpp -o obj/Wall.o

bin:
	mkdir bin

obj:
	mkdir obj