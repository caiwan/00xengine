CC = g++
PREFLAGS = -Wall -g -fPIC -Isrc/ -Isrc/Extern/freetype/ -lGL -lSDL_image `/usr/local/bin/sdl-config --cflags --libs` `freetype-config --cflags --libs` 

ifeq ($(DEBUG),1)
CFLAGS = $(PREFLAGS) -D_DEBUG
else
CFLAGS = $(PREFLAGS)
endif

CLIBFLAGS = $(CFLAGS) -shared

.PHONY: all, main, engine, clean

all:
	@echo -ne "\e[0m"
	make engine
	make main

main:
	$(CC) $(CFLAGS) -Lbin/ -l00x Scene.cpp main.cpp -o bin/engine

engine:
ifeq ($(DEBUG),1)
	make -C src/ DEBUG=1
else
	make -C src/
endif
	$(CC) $(CLIBFLAGS) src/*.o -o bin/lib00x.so 
	@echo -e "\e[1;31m## \e[1;37mShared Library Compiled! \e[1;31m##\e[0;0m"

clean:
	rm -f `find ./src/ -name *.o`
	

