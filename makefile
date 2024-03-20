CC=clang
CFLAGS=-g -Wall -Wextra -std=c17
OUTPUT_BASE:=pong_out
RM:=rm

ifeq ($(OS), Windows_NT)
	OUTPUT:=$(OUTPUT_BASE).exe
	RM:=del
else
	OUTPUT:= $(OUTPUT_BASE)
endif


SFMLFLIBS=-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
SFMLLINK=C:/Dev/CSFML-2.5.1/lib/msvc
SFMLINC=C:/Dev/CSFML-2.5.1/include

BINS=$(OUTPUT)

build: $(BINS)
	
$(OUTPUT): 
	$(CC) src/*.c $(CFLAGS) -I include -I $(SFMLINC) -L $(SFMLLINK) -o $@ $(SFMLFLIBS) 

run:
	.\$(OUTPUT)

clean:
	$(RM) $(OUTPUT_BASE)*


