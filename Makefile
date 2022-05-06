bomb1.o: bomb1.cpp bomb1.h
	g++ -pedantic-errors -std=c++11 -c bomb1.cpp

bomb2.o: bomb2.cpp bomb2.h
	g++ -pedantic-errors -std=c++11 -c bomb2.cpp

main.o: main.cpp bomb1.h bomb2.h
	g++ -pedantic-errors -std=c++11 -c main.cpp

othellobomb: bomb1.o bomb2.o main.o
	g++ -pedantic-errors -std=c++11 bomb1.o bomb2.o main.o -o othellobomb 
  
