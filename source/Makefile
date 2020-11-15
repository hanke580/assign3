
assign3: assign3part2.o pagetable.o phyframes.o
	gcc assign3part2.o pagetable.o phyframes.o -o assign3
assign3part2.o: assign3part2.c
	gcc -c assign3part2.c -o assign3part2.o
pagetable.o: pagetable.c
	gcc -c pagetable.c -o pagetable.o
phyframes.o: phyframes.c
	gcc -c phyframes.c -o phyframes.o

clean:
	rm -rf *.o