all: main
	echo privet

main: Input.o main.o Output.o SquareSolver.o SquareSolverTest.o
	g++ Input.o main.o Output.o SquareSolver.o SquareSolverTest.o -o main

Input.o: Input.cpp
	g++ -c Input.cpp

main.o: main.cpp
	g++ -c main.cpp

Output.o: Output.cpp
	g++ -c Output.cpp

SquareSolver.o: SquareSolver.cpp
	g++ -c SquareSolver.cpp

SquareSolverTest.o: SquareSolverTest.cpp
	g++ -c SquareSolverTest.cpp

link:
	g++ main.o SquareSolver.o Input.o Output.o SquareSolverTest.o

buildh:
	g++ SquareSolver.h Input.h Output.h SquareSolverTest.h

start:
	.\main.exe

clean:
	rm *.o
	rm *.exe