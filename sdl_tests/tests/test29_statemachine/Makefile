DEMO=wrpg_statemachine
CC=gcc

SRC = $(wildcard ./*.c)
OBJ = $(addprefix obj/,$(notdir $(SRC:.c=.o)))

CFLAGS= -I. -I../../src -std=gnu99 -Wall -Werror -Wno-unused -O3 -g

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	OUT=$(DEMO)
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	OUT=$(DEMO).exe
	LFLAGS= ../../worldrpg.res -lmingw32 
endif

ifeq ($(findstring MSYS,$(PLATFORM)),MSYS)
	OUT=$(DEMO).exe
	LFLAGS= ../../worldrpg.res -lmingw32 
endif

obj/%.o: ./%.c | obj
	$(CC) $< -c $(CFLAGS) -o $@

obj:
	mkdir obj

$(OUT): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@
	
clean:
	rm $(OUT) $(OBJ)

