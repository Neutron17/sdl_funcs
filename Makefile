CC = clang

PNAME = c

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN = build

EXEC = $(BIN)/$(PNAME)
INCFLAGS  = -Isrc/

CCFLAGS += $(INCFLAGS)
CCFLAGS += -O0
CCFLAGS += -Wall
CCFLAGS += -pedantic

LDFLAGS  = $(INCFLAGS)
LDFLAGS += -lSDL2
LDFLAGS += -lm

all: build

run: build
	$(BIN)/c $*

build: $(OBJ)
	$(CC) $(CCFLAGS) -ggdb -o $(BIN)/c $(filter %.o,$^) $(LDFLAGS)

clean:
	rm $(BIN)/* $(OBJ)

%.o: %.c
	$(CC) -ggdb -o $@ -c $< $(CCFLAGS)

