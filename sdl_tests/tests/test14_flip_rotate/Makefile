DEMO=wrpg_flip_rotate
CC=gcc

CFLAGS= -I. -I../../src -std=gnu99 -Wall -Werror -Wno-unused -O3 -g

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	OUT=$(DEMO)
	LFLAGS= -lGL -lSDL2 -lSDL2_mixer -lSDL2_image
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	OUT=$(DEMO).exe
	LFLAGS= ../../worldrpg.res -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lopengl32
endif

ifeq ($(findstring MSYS,$(PLATFORM)),MSYS)
	OUT=$(DEMO).exe
	LFLAGS= ../../worldrpg.res -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lopengl32
endif

$(OUT): test_14_flip_rotate.c WRPG_sprite.c
	$(CC) test_14_flip_rotate.c WRPG_sprite.c $(CFLAGS) $(LFLAGS) -o $@
	
clean:
	rm $(OUT)

