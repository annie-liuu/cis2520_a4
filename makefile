a4:	main.o graph_functions.o
	gcc main.o graph_functions.o -o a4
main.o:	main.c graph.h
	gcc -Wall -std=c99 -c -pedantic main.c
graph_functions.o:	graph_functions.c graph.h
	gcc -Wall -std=c99 -c -pedantic graph_functions.c
clean:
	rm *.o a4