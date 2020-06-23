install: exe.o partie1.o partie2.o partie3.o partie4.o
	gcc -Wall exe.o partie1.o partie2.o partie3.o partie4.o -o exe

 exe.o: exe.c final.h
	gcc -Wall -c exe.c

 partie1.o: partie1.c final.h
	gcc -Wall -c partie1.c

 partie2.o: partie2.c final.h
	gcc -Wall -c partie2.c

 partie3.o: partie3.c final.h
	gcc -Wall -c partie3.c

 partie4.o: partie4.c final.h
	gcc -Wall -c partie4.c	
clean:
	rm *.o exe	
