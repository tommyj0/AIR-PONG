CC=clang
CFLAGS= -g -Wall -Wextra -std=c99 -lm
BUILD_DIR:=bin
RM:=rm
OUTPUT_NAME:=PONG

OUTPUT_PATH:=$(BUILD_DIR)/$(OUTPUT_NAME)
OUTPUT:=$(OUTPUT_PATH)


SFMLDIR=./ext/CSFML
SFMLFLIBS=-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
SFMLLINK=$(SFMLDIR)/build/lib
SFMLINC=$(SFMLDIR)/include

export LD_LIBRARY_PATH := $(SFMLLINK)

BINS=$(OUTPUT)
DEBUG_BINS=$(OUTPUT)

build: $(BINS)

debug: $(DEBUG_BINS)
	
$(OUTPUT): 
	mkdir bin
	$(CC) src/*.c $(CFLAGS) -I inc -I $(SFMLINC) -L $(SFMLLINK) -o $@ $(SFMLFLIBS) 
run: build
	./$(OUTPUT)

clean:
	$(RM) $(BUILD_DIR)


