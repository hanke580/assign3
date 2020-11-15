#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include "phyframes.h"
#include "pagetable.h"


// The number of pages will be used for the kernel
#define KERNEL_PAGES 1
#define REAL_PAGE_SIZE 4096


char * sequenceFileName;
char * outputFileName;

void analyzeAccessSequenceFromFile(char * fileName, char * outfileName) {
	// Open this file 
	int fd;
	struct stat st;
	unsigned long filesize;
	unsigned long mapsize;

	unsigned long * memAccesses;
	stat(fileName, &st);

	filesize = st.st_size;


	fd = open(fileName, O_RDONLY); 
	if(fd == -1) {
		fprintf(stderr, "fd is invalid, with error %s\n", strerror(errno));
		exit(-1);
	}

    mapsize = ((filesize + (REAL_PAGE_SIZE - 1)) & ~(REAL_PAGE_SIZE - 1));

	memAccesses = (unsigned long *)mmap(0, mapsize, PROT_READ, MAP_PRIVATE, fd, 0);
	if(memAccesses == MAP_FAILED) {
		fprintf(stderr, "mmap the input file failed. \n");
		exit(-1);
    }

	fprintf(stderr, "map starting %p filesize %ld\n", memAccesses, filesize);
	
    FILE *od = fopen(outfileName, "wb");
    if(od == NULL) {
		fprintf(stderr, "fd is invalid, with error %s\n", strerror(errno));
		exit(-1);
    }

	// Traverse all memory accesses of the file
	for(int i = 0; i < filesize/sizeof(unsigned long); i++) {
		// Simulate the running
        unsigned long high = memAccesses[i] >> 7;
        unsigned long low = memAccesses[i] & ((1 << 7) - 1);
        int frameInd = fetch(&PF, high);
        unsigned long res = low + (frameInd << 7);        
        fprintf(stderr, "%d: %lx\n", i, memAccesses[i]);
        fwrite(&res, sizeof(res), 1, od);
	} 

}



int main(int argc, char ** argv) {
	int i;
	int accesses; 
    ptInit();
    phyInit();

	sequenceFileName = argv[1];
	outputFileName = "output-part2";
	// Check whether the sequence file is existing and I can access this file?
	if(access(sequenceFileName, F_OK ) == -1 ) {
    fprintf(stderr, "The sequence file %s is not existing\n", sequenceFileName);
		exit(-1);
	} 


	// Now analyze the access sequence of the input sequence file
	analyzeAccessSequenceFromFile(sequenceFileName, outputFileName);

    printf("pageFaultCount = %d\n", pageFaultCount);
}
