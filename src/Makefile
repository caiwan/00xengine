CC = g++
PREFLAGS = -Wall -g -c -I. -IExtern/freetype/ -fPIC -lGL -lSDL_Image `/usr/local/bin/sdl-config --cflags --libs` `freetype-config --cflags --libs`
OBJECTS=\
Core/Camera.o\
Core/DataManager.o\
Core/Entity.o\
Core/FontManager.o\
Core/Frustum.o\
Core/Image.o\
Core/Input.o\
Core/Kernel.o\
Core/Resource.o\
Core/ResourceManager.o\
Core/Settings.o\
Core/Window.o\
Debug/Exceptions.o\
Debug/Logger.o\
Debug/MemoryManager.o\
Loaders/ImageLoader.o\
Loaders/LoadersManager.o\
Math/AABB.o\
Math/Mathlib.o\
Math/Rectangle.o\
Math/Matrix4.o\
Renderer/Renderer.o\
Renderer/Shader.o\
Renderer/Text.o\
Renderer/Texture.o\
Renderer/VAO.o\
Renderer/VBO.o\
Task/InputTask.o\
Task/SceneTask.o\
Utils/Clock.o\
Utils/Color.o\
Utils/File.o\
Utils/StringConverter.o

ifeq ($(DEBUG),1)
CFLAGS = $(PREFLAGS) -D_DEBUG
else
CFLAGS = $(PREFLAGS)
endif


.PHONY: all, cleancp, clean

all: $(OBJECTS)
	@echo -e "\e[1;31m## \e[1;37mCore Compiled! \e[1;31m##\e[0;0m"

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(/usr/local/bin/sdl-config --cflags --libs)
	cp $@ ./

cleancp:
	rm -f *.o
