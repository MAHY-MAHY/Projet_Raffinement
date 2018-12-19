exe : main.o cellule.o lax_friedrichs.o maillage.o
	g++ -o exe main.o cellule.o lax_friedrichs.o maillage.o
cellule.o : cellule.cpp cellule.h
	g++ -c cellule.cpp -o cellule.o
lax_friedrichs.o : cellule.h maillage.h lax_friedrichs.h lax_friedrichs.cpp
	g++ -c lax_friedrichs.cpp -o lax_friedrichs.o
maillage.o :cellule.h maillage.h maillage.cpp
	g++ -c maillage.cpp -o maillage.o 
main.o : main.cpp cellule.h
	g++ -c main.cpp -o main.o
clean :
	rm *.o
