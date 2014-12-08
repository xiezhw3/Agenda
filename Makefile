
agenda : Date.o User.o Meeting.o Json.o Storage.o AgendaService.o AgendaUI.o \
	     main.o
	g++ -std=c++0x -o agenda Date.o User.o Meeting.o Json.o Storage.o \
	AgendaService.o AgendaUI.o main.o

Date.o : Date.h Date.cpp
	g++ -std=c++0x -c Date.cpp

User.o : User.h User.cpp
	g++ -std=c++0x -c User.cpp

Meeting.o : Meeting.h Meeting.cpp
	g++ -std=c++0x -c Meeting.cpp

Json.o : Json.h Json.cpp
	g++ -std=c++0x -c Json.cpp

Storage.o : Storage.h Storage.cpp
	g++ -std=c++0x -c Storage.cpp

AgendaService.o : AgendaService.h AgendaService.cpp
	g++ -std=c++0x -c AgendaService.cpp

AgendaUI.o : AgendaUI.h AgendaUI.cpp
	g++ -std=c++0x -c AgendaUI.cpp

main.o : main.cpp
	g++ -std=c++0x -c main.cpp

clean :
	rm *.o *~
