CC=clang
CFLAGS=-g -Wall -Wextra -std=c17
BUILD_DIR:=bin
RM:=rm
OUTPUT_NAME:=PONG

ifeq ($(OS), Windows_NT)
	OUTPUT_PATH:=$(BUILD_DIR)\$(OUTPUT_NAME)
	OUTPUT:=$(OUTPUT_PATH).exe
	RM:=del
else
	OUTPUT_PATH:=$(BUILD_DIR)/$(OUTPUT_NAME)
	OUTPUT:=$(OUTPUT_PATH)
endif


SFMLFLIBS=-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
SFMLLINK=C:/Dev/CSFML-2.5.1/lib/msvc
SFMLINC=C:/Dev/CSFML-2.5.1/include

BINS=$(OUTPUT) clear_debug 
DEBUG_BINS=$(OUTPUT)

build: $(BINS)

debug: $(DEBUG_BINS)
	
$(OUTPUT): 
	$(CC) src/*.c $(CFLAGS) -I inc -I $(SFMLINC) -L $(SFMLLINK) -o $@ $(SFMLFLIBS) 

clear_debug:
	$(RM) $(OUTPUT_PATH).pdb $(OUTPUT_PATH).ilk

run:
	.\$(OUTPUT)

clean:
	$(RM) $(OUTPUT_PATH)*


