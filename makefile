CC=clang
CFLAGS=-g -Wall -Wextra -std=c17
BINS=game

SFMLFLIBS=-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
SFMLLINK=C:/Dev/CSFML-2.5.1/lib/msvc
SFMLINC=C:/Dev/CSFML-2.5.1/include

build: $(BINS)
	
game: 
	$(CC) src/*.c $(CFLAGS) -I include -I $(SFMLINC) -L $(SFMLLINK) -o $@.exe $(SFMLFLIBS) 

clean:
	del game.*



