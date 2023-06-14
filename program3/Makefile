
#
#  To sa opcje dla kompilacji
#
CXXFLAGS= -c -g -Iinc -Wall -pedantic

__start__: KolkoIKrzyzyk
	./KolkoIKrzyzyk

KolkoIKrzyzyk: obj/main.o 
	g++ -Wall -pedantic -o KolkoIKrzyzyk obj/main.o

obj/main.o: src/main.cpp inc/AI.hpp inc/plansza.hpp
	g++ ${CXXFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -f obj/*.o main.o