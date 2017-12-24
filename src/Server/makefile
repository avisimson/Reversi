#AviSimson205789100
#YakirPinchas203200530
a.out: ReversiServer.o main.o
	g++ main.o ReversiServer.o 

ReversiServer.o: ReversiServer.cpp ReversiServer.h
	g++ -c ReversiServer.cpp

main.o: main.cpp ReversiServer.h
	g++ -c main.cpp

