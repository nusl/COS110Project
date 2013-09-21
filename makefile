# Temporary test makefile - not final!

RPG: src/*.h src/*.cpp
	g++ --static -Wall -Werror src/*.cpp -o bin/RPG
