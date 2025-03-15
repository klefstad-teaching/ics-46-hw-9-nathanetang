CXXFLAGS=-ggdb -std=c++20 -Wall -Wextra -Wfatal-errors -pedantic

main: src/ladder_main.cpp src/ladder.cpp
	g++ $(CXXFLAGS) src/ladder_main.cpp src/ladder.cpp -o main

clean:
	/bin/rm main
