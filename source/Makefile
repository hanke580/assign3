
assign3: assign3part3.o pagetable.o phyframes.o
	gcc assign3part3.o pagetable.o phyframes.o -o assign3 -lm
assign3part3.o: assign3part3.c
	gcc -c -lm assign3part3.c -o assign3part3.o
pagetable.o: pagetable.c
	gcc -c pagetable.c -o pagetable.o
phyframes.o: phyframes.c
	gcc -c phyframes.c -o phyframes.o

clean:
	rm -rf *.o