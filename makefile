all:
	gcc src/*.c -Isrc -g -Wall -Wextra -I C:/Dev/CSFML-2.5.1/include  -o bin/csfmlgame -L C:/Dev/CSFML-2.5.1/lib/gcc -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio && bin/csfmlgame

