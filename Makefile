#
#  To sa opcje dla kompilacji
#
CXXFLAGS= -c -g -Iinc -Wall -pedantic

__start__: program1
	./program1

program1: main.o kolejkaprio.o elementkol.o
	g++ -Wall -pedantic -o program1 main.o kolejkaprio.o elementkol.o

main.o: main.cpp kolejkaprio.hh elementkol.hh
	g++ ${CXXFLAGS} -o main.o main.cpp

kolejkaprio.o: kolejkaprio.cpp kolejkaprio.hh elementkol.hh
	g++ ${CXXFLAGS} -o kolejkaprio.o kolejkaprio.cpp

elementkol.o: elementkol.cpp elementkol.hh
	g++ ${CXXFLAGS} -o elementkol.o elementkol.cpp


clean:
	rm -f obj/*.o uklad_rownan