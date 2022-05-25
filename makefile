
CC = clang-9 
CXXFLAGS= -Werror 
.PHONY: all clean



main: main.o singleton.o
	$(CC) $(CXXFLAGS) -o main main.o singleton.o -lstdc++ 

test_g: test_guard.o guard.o
	$(CC) $(CXXFLAGS) -o test_g test_guard.o guard.o -pthread -lstdc++

server: server.o aa.so
	$(CC) $(CXXFLAGS) -pthread -fPIE -fPIC -o server server.o ./aa.so

client: client.o 
	$(CC) $(CXXFLAGS) -pthread -o client client.o




aa.so: main1.o
	$(CC) $(CXXFLAGS) -shared -fPIC -fPIE -o aa.so main1.o 



main1.o: main1.cpp main1.hpp
	$(CC) $(CXXFLAGS)  -c main1.cpp -fPIE

client.o: client.cpp 
	$(CC) $(CXXFLAGS) -c client.cpp -fPIE

server.o: server.cpp 
	$(CC) $(CXXFLAGS) -c server.cpp -fPIE

test.o: test.cpp
	$(CC) $(CXXFLAGS) -c test.cpp 

main.o: main.cpp 
	$(CC) $(CXXFLAGS)  -c main.cpp -fPIE

test_guard.o: test_guard.cpp guard.hpp
	$(CC)  -c test_guard.cpp 

guard.o: guard.cpp guard.hpp
	$(CC)  -c guard.cpp 

singleton.o: singleton.cpp 
	$(CC) $(CXXFLAGS) -c singleton.cpp -fPIE




clean:
	rm -rf *.o *.so *.a test main client server