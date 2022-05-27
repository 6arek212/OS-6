
CC = clang-9 
CXXFLAGS= -Werror 
.PHONY: all clean test


test: test_guard test_singleton
	./test_guard
	./test_singleton


main: main.o singleton.o
	$(CC) $(CXXFLAGS) -o main main.o singleton.o -lstdc++ 

server: server.o aa.so
	$(CC) $(CXXFLAGS) -pthread -fPIE -fPIC -o server server.o ./aa.so

poll_server: poll_server.o reactor.o 
	$(CC) $(CXXFLAGS) -pthread -fPIE -fPIC -o poll_server poll_server.o reactor.o 

client: client.o 
	$(CC) $(CXXFLAGS) -pthread -o client client.o


# test programs

test_guard: test_guard.o aa.so
	$(CC) $(CXXFLAGS) -o test_guard test_guard.o ./aa.so -pthread -lstdc++

test_singleton: test_singleton.o aa.so
	$(CC) $(CXXFLAGS) -o test_singleton test_singleton.o ./aa.so -pthread -lstdc++


aa.so: main1.o reactor.o guard.o singleton.o
	$(CC) $(CXXFLAGS) -shared -fPIE -o aa.so main1.o reactor.o guard.o singleton.o



main1.o: main1.cpp main1.hpp
	$(CC) $(CXXFLAGS) -c main1.cpp -fPIE -fPIC

client.o: client.cpp 
	$(CC) $(CXXFLAGS) -c client.cpp -fPIE

server.o: server.cpp 
	$(CC) $(CXXFLAGS) -c server.cpp -fPIE
	
poll_server.o: poll_server.cpp 
	$(CC) $(CXXFLAGS) -c poll_server.cpp -fPIE

main.o: main.cpp 
	$(CC) $(CXXFLAGS)  -c main.cpp -fPIE

guard.o: guard.cpp guard.hpp
	$(CC)  -c guard.cpp 

singleton.o: singleton.cpp 
	$(CC) $(CXXFLAGS) -c singleton.cpp -fPIE

reactor.o: reactor.cpp reactor.hpp
	$(CC) $(CXXFLAGS) -c reactor.cpp -fPIE





test_guard.o: test_guard.cpp guard.hpp
	$(CC)  -c test_guard.cpp 

test_singleton.o: test_singleton.cpp
	$(CC) $(CXXFLAGS) -c test_singleton.cpp 



clean:
	rm -rf *.o *.so *.a test main client server poll_server test_guard test_singleton