
CC = clang-9 
CXXFLAGS= -Werror 
.PHONY: all clean






main: main.o queue.o
	$(CC) $(CXXFLAGS) -o main main.o queue.o -pthread -lstdc++

test: test_guard.o guard.o
	$(CC) $(CXXFLAGS) -o test test_guard.o guard.o -pthread -lstdc++


server: server.o queue.o active_object.o
	gcc -pthread -o server server.o queue.o active_object.o




active_object.o: active_object.hpp
	$(CC) $(CXXFLAGS) -c active_object.hpp 

server.o: server.c
	$(CC) -c server.c 

test.o: test.cpp
	$(CC) $(CXXFLAGS) -c test.cpp 

main.o: main.cpp
	$(CC)  -c main.cpp 

queue.o: queue.cpp
	$(CC)  -c queue.cpp 

test_guard.o: test_guard.cpp guard.hpp
	$(CC)  -c test_guard.cpp 

guard.o: guard.cpp guard.hpp
	$(CC)  -c guard.cpp 





clean:
	rm -rf *.o test main