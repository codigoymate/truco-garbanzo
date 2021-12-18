SRC = $(wildcard src/*.c)
OBJ = $(addprefix obj/, $(notdir $(SRC:.c=.o)))

CFLAGS = -Wall -pedantic -g -I include
LFLAGS = -lncurses
BINARY = bin/truco

all: $(BINARY)

$(BINARY): $(OBJ) | bin
	gcc $(CFLAGS) $(OBJ) -o $(BINARY) $(LFLAGS)

obj/%.o: src/%.c | obj
	gcc $(CFLAGS) $< -o $@ -c

obj:
	mkdir obj

bin:
	mkdir bin

run: $(BINARY)
	@$(BINARY)

.PHONY=clean
clean:
	rm -f $(OBJ) $(BINARY)