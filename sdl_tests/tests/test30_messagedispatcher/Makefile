DEMO=wrpg_messagedispatcher
CC=gcc

SRC = $(wildcard ./*.c)
OBJ = $(addprefix obj/,$(notdir $(SRC:.c=.o)))

CFLAGS= -I. $(shell pkg-config --cflags glib-2.0) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	OUT=$(DEMO)
	LFLAGS= $(shell pkg-config --libs glib-2.0) 
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	OUT=$(DEMO).exe
	LFLAGS= ../../worldrpg.res -lmingw32 $(shell pkg-config --libs glib-2.0) 
endif

ifeq ($(findstring MSYS,$(PLATFORM)),MSYS)
	OUT=$(DEMO).exe
	LFLAGS= ../../worldrpg.res -lmingw32 $(shell pkg-config --libs glib-2.0) 
endif

obj/%.o: ./%.c | obj
	$(CC) $< -c $(CFLAGS)  -o $@

obj:
	mkdir obj

$(OUT): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@
	
clean:
	rm $(OUT) $(OBJ)

