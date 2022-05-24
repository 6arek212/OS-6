
CC = clang-9 
CXXFLAGS= -Werror 
.PHONY: all clean



main: main.o singleton.o
	$(CC) $(CXXFLAGS) -o main main.o singleton.o -lstdc++ 

test_g: test_guard.o guard.o
	$(CC) $(CXXFLAGS) -o test_g test_guard.o guard.o -pthread -lstdc++

server: server.o main1.o
	gcc -pthread -fPIE -o server server.o main1.o 

client: client.o 
	$(CC) -pthread -o client client.o




main1.o: main1.cpp 
	$(CC) $(CXXFLAGS)  -c main1.cpp -fPIE

client.o: client.cpp 
	$(CC) $(CXXFLAGS) -c client.cpp -fPIE

active_obj.o: active_obj.cpp active_obj.hpp
	$(CC) $(CXXFLAGS) -c active_obj.cpp  -fPIE

server.o: server.cpp 
	$(CC) $(CXXFLAGS) -c server.cpp -fPIE

test.o: test.cpp
	$(CC) $(CXXFLAGS) -c test.cpp 

main.o: main.cpp 
	$(CC) $(CXXFLAGS)  -c main.cpp -fPIE

queue.o: queue.cpp
	$(CC)  -c queue.cpp 

test_guard.o: test_guard.cpp guard.hpp
	$(CC)  -c test_guard.cpp 

guard.o: guard.cpp guard.hpp
	$(CC)  -c guard.cpp 

singleton.o: singleton.cpp 
	$(CC) $(CXXFLAGS) -c singleton.cpp -fPIE




clean:
	rm -rf *.o test main client server