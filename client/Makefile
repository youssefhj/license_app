COMPILER = gcc
CFLAGS = -g -Wall -Werror

OBJ = build/obj
BIN = build/bin

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(OBJ)/%.o, $(SRCS))

OUT = $(BIN)/client.exe

all: $(OUT)

$(OUT): $(OBJS) $(OBJ)/dgsocket.o
	$(COMPILER) $(CFLAGS) $^ -o $@

$(OBJ)/%.o: %.c
	gcc -c $< -o $@

$(OBJ)/dgsocket.o: ../lib/dgsocket.c ../lib/dgsocket.h
	gcc -c $< -o $@

clean:
	rm -r $(OBJ)/* $(BIN)/*