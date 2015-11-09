run_algo: main.o dijkstra.o floyd_warshal.o
	g++ main.o dijkstra.o floyd_warshal.o -o run_algo -lrt
main.o: header.h dijkstra.h floyd_warshal.h
	g++ -o main.o -c main.cpp
dijkstra.o: header.h dijkstra.h
	g++ -o dijkstra.o -c dijkstra.cpp
floyd_warshal.o: header.h floyd_warshal.h
	g++ -o floyd_warshal.o -c floyd_warshal.cpp
clean:
	rm *.o
