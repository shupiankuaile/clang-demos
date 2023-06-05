DEMO=keyboard
CC=gcc

CFLAGS= -I../../src -std=gnu99 -Wall -Werror -Wno-unused -O3 -g

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	OUT=$(DEMO)
	LFLAGS= -lGL -lSDL2 -lSDL2_mixer 
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	OUT=$(DEMO).exe
	LFLAGS= ../../worldrpg.res -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lopengl32
endif

ifeq ($(findstring MSYS,$(PLATFORM)),MSYS)
	OUT=$(DEMO).exe
	LFLAGS= ../../worldrpg.res -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lopengl32
endif

$(OUT): test_3_keyborad.c
	$(CC) $< $(CFLAGS) $(LFLAGS) -o $@
	
clean:
	rm $(OUT)

