
CC = clang-9 
CXXFLAGS= -Werror 
.PHONY: all clean






main: main.o queue.o
	$(CC) $(CXXFLAGS) -o main main.o queue.o -pthread -lstdc++

test: test_guard.o guard.o
	$(CC) $(CXXFLAGS) -o test test_guard.o guard.o -pthread -lstdc++


server: server.o queue.o active_obj.o
	gcc -pthread -fPIE -o server server.o queue.o active_obj.o 

client: client.o 
	$(CC) -pthread -o client client.o



client.o: client.cpp 
	$(CC) $(CXXFLAGS) -c client.cpp -fPIE

active_obj.o: active_obj.cpp active_obj.hpp
	$(CC) $(CXXFLAGS) -c active_obj.cpp  -fPIE

server.o: server.cpp active_obj.hpp queue.hpp
	$(CC) $(CXXFLAGS) -c server.cpp -fPIE

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
	rm -rf *.o test main client server