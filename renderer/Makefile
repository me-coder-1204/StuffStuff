
compile: 
	g++ -W -Wall -Wextra -pedantic -o main main.cpp ./headers/graph.cpp ./headers/application.cpp ./headers/player.cpp ./headers/raycast.cpp -Iinclude -lpthread -Llib -lSDL2 -lSDL2main -lstdc++ -lm -ggdb3
	# valgrind --leak-check=full \
    #      --show-leak-kinds=all \
    #      --track-origins=yes \
    #      --verbose \
    #      --log-file=valgrind-out.txt \
         ./main