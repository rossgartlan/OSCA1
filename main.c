#include <stdio.h>
#include <stdlib.h>
#include "lib/my-functions.h"
#include <time.h>

#define allocated 65536
#define min 2048
#define max 20480
#define minAscii 33
#define maxAscii 126
#define memMin 512
#define bytesPerFrame 2
#define OFFSET_BITS 8
#define pageTableSizeBytes 512
#define pageSize 256


//16 bit page frame number
unsigned short pfn = 0x32;
unsigned short offset = 0xAB;

int randomNum();
unsigned short allocateMemory();
void randomAscii();
void constructPhysicalAddress();
void writeToPageTable();


int main() {

   unsigned short *mem;
   mem  =  (unsigned short*)malloc(sizeof(allocated));

   // gets a random number 2048-20480 bytes and assigns to memory
   int num = randomNum();
   // writes a one character ascii to the block of memory allocated
   randomAscii(mem,num);
   // writes a page table to the first 512 bytes of the page table
   int tableSize = sizeof(pageTableSizeBytes);
   writeToPageTable(mem,tableSize);
   constructPhysicalAddress();
   return 0;
}

int randomNum(){
   // Randomly get between 2048 and 20480 bytes
   srand(time(0));
   int assigned = rand() % (max- min + 1) + min;
   printf("%d\n", assigned);
   return assigned;
}

void randomAscii(unsigned short *mem,int num){
   // Randomly create a number between 33 and 126 that is the equivilant of 1 char in ascii table
   char values[num];
   // Print the memory alocated to a text file
   srand(time(0));
   // populate memory array with characters
   for(int i = memMin; i < num ; i ++){
      int asciiNum = rand() % (maxAscii- minAscii + 1) + minAscii;
      char c = asciiNum;
      //printf("%c",c);
      mem[i]=c;
      values[i]=c;
   }
   // Print the memory alocated to a text file
   int frameNum=2;
   int count = 0;
   FILE *f;
   f  = fopen("data/physical_memory.txt", "w");
   fprintf(f,"      Address       |       Frame     |    Content \n");
   fprintf(f,"----------------------------------------------------\n");
   for(int i = memMin; i < num; i ++){
     //if(mem[i] != 0){
     if(count < pageSize){
       fprintf(f,"%s %p %s %d %s %c \n"," ",&mem[i],"           ",frameNum,"             ",values[i]);
       count ++;
     }
     else{
       count = 0;
       frameNum ++;
    }
  }
}

void constructPhysicalAddress(){
    unsigned short address = pfn << OFFSET_BITS;
    address |= offset;
    printf("PFN: 0x%x and offset: 0x%x = address: 0x%x\n", pfn, offset, address);
}

void writeToPageTable(unsigned short *mem, int tableSize){
   // This is creating the page table for a single process
   FILE *f;
   f  = fopen("data/page_table.txt", "w");
   fprintf(f,"   Page   | Page Table Entry |\n");
   fprintf(f,"------------------------------\n");

   for(int i = 0; i < pageSize; i++){
     mem[i]= ("%02x", i);
     fprintf(f, "%s %02x %s %02x\n", "   ", i, "          " , i + 2);
    }
    // Now adding 2 values to the page table which are not in physical memory
    fprintf(f,"  Pages not stored in memory  \n");
    fprintf(f,"------------------------------\n");
    for(int i = pageSize;i < pageSize +2 ; i ++){
       fprintf(f, "%s %02x %s %s", "   ", i, "        " , " Disk\n");
    }
}


