a.out:Date.o Storage.o Meeting.o User.o AgendaService.o AgendaUI.o
	g++ -std=c++0x Agenda.cpp Date.o Storage.o Meeting.o User.o AgendaService.o AgendaUI.o -o a.out
	
AgendaUI.o:AgendaUI.h AgendaUI.cpp
	g++ -std=c++0x AgendaUI.cpp -c -g
	
AgendaService.o:AgendaService.h AgendaService.cpp
	g++ -std=c++0x AgendaService.cpp -c -g
	
Storage.o:Storage.h Storage.cpp
	g++ -std=c++0x Storage.cpp -c -g
	
Date.o:Date.h Date.cpp
	g++ -std=c++0x Date.cpp -c -g
	
Meeting.o:Meeting.h Meeting.cpp
	g++ -std=c++0x Meeting.cpp -c -g
	
User.o:User.h User.cpp
	g++ -std=c++0x User.cpp -c -g
	
clean:
	rm *.o a.out
	

