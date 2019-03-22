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
#define minPT 128
#define maxPT 512

int randomNum();
int randomNumOffsetPT();
unsigned short allocateMemory();
void randomAscii();
void writeToPageTable();
void userInputHex();


int main() {

   unsigned short *mem;
   mem  =  (unsigned short*)malloc(sizeof(allocated));
   // gets a random number 2048-20480 bytes and assigns to memory
   int num = randomNum();
   // Getting a random offset from the page table to start writing block of mem
   int offsetPT = randomNumOffsetPT();
   //unsigned short *values;
   // writes a one character ascii to the block of memory allocated
   int tableSize = sizeof(pageTableSizeBytes);
   // writes a page table to the first 512 bytes of the page table
   writeToPageTable(mem,tableSize);
   randomAscii(mem,num,offsetPT);

   return 0;
}

int randomNum(){
   // Randomly get between 2048 and 20480 bytes
   srand(time(0));
   int assigned = rand() % (max - min + 1) + min;
   printf("%d\n", assigned);
   return assigned;
}

int randomNumOffsetPT(){
   // Randomly get between 2048 and 20480 bytes
   srand(time(0));
   int assigned = rand() % (maxPT - minPT  + 1) + minPT;
   return assigned;
}


void randomAscii(unsigned short *mem,int num,int offsetPT){
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
   fprintf(f,"      Address     |     Frame     |    Content \n");
   fprintf(f,"-----------------------------------------------\n");
   for(int i = memMin+512; i < num; i ++){
     //if(mem[i] != 0){
     if(count < pageSize){
       fprintf(f,"%s %04x %s %d %s %c \n"," ",i,"\t\t\t",frameNum,"\t\t ",values[i]);
       count ++;
     }
     else{
      count = 0;
      frameNum ++;
    }
   } 

   fflush(f);
   
   // Write to text file simulated storage 
   char swapSpace[pageTableSizeBytes];
   int frameSP = 0;
   int countSP = 0;
   FILE *fn;
   fn  = fopen("data/swap_space.txt", "w");
   fprintf(fn,"      Address     |   Frame   |    Content    \n");
   fprintf(fn,"----------------------------------------------\n");
   for(int i = 0; i < 512; i++){
   int asciiNum = rand() % (maxAscii- minAscii + 1) + minAscii;
   char c = asciiNum;
   swapSpace[i]=c;
   if(countSP < pageSize){
     fprintf(fn,"%s %02x %s %d %s %c\n","\t",i,"\t\t",frameSP,"\t\t",swapSpace[i]);
     countSP ++;
    }
    else{
      countSP = 0;
      frameSP ++;
    }
   }
   printf("Console print of sample addresses that point to pages not in physical memory");    
   printf("0x10\n");
   printf("0x101\n");
   
   fflush(fn);
   int maxVirAddress = num+512;
   unsigned int value;
   // creating a do/while loop for user input until ctrl c or -1 entered
   do{
      printf("Enter a virtual Address value in hexidecimal form without 0x: \n ");
   		scanf("%x", &value);
   		printf("Value = 0x%x\n",value);
   		if(value < 0x200){
         printf("This value is not is physical memory\n");
         printf("Now loading frame from swapspace into memory");
         if(value > 0xff){
           for(int i = 256;i < 512; i ++){
              mem[i+512]=swapSpace[i];
          }
         }
         else{
           for(int i = 0;i < 256;  i++){
              mem[i+512]=swapSpace[i];
           }
         }
   		}
   		else if(value > maxVirAddress){
        printf("This address is not used\n");
   		}
   		else{
   		printf("The first step is to split the address into 2 parts its virtual address and its offset\n");
   		unsigned int result = 0;
   		unsigned int divisor = 0;
   		divisor = value / 0x100;
   		printf("divisor this is the equivilant of the page table number: %u\n",divisor);
   		result = value - (0x100 * divisor);
   		printf("Mod this is the equivilant of the offset: %u\n", result);
   		printf("The next step is to look up the page table and find the frame\n");
   		printf("The mapped frame number from the page number is %d\n", divisor +2);
   		unsigned int physicalAddress = 0;
   		physicalAddress = (divisor * 0x100) + result;
   		physicalAddress = physicalAddress + 512;
   		printf("the physical address is %x\n", physicalAddress);
   		printf("The value of the physical address is %c\n",mem[physicalAddress]);
     }
   }
   
   while(value != -1);
}

void writeToPageTable(unsigned short *mem, int tableSize){
   // This is creating the page table for a single process
   FILE *f;
   f  = fopen("data/page_table.txt", "w");
   fprintf(f,"   Page   | Page Table Entry |\n");
   fprintf(f,"------------------------------\n");

   for(int i = 0;i < 2 ; i ++){
     fprintf(f, "%s %02x %s %s", "   ", i, "\t\t" , " Disk\n");
   }

   //writing to the console human readable form of one page table entry
   printf("Example of a page table entry printed to the console\n");
   
   for(int i = 2; i < pageSize; i++){
     mem[i] = i;
     if(i == pageSize -1){
       fprintf(f, "%s %02x %s %02x\n", "   ", i, "\t\t " , 0);
       
     }
     else if(i == pageSize - 2){
       fprintf(f, "%s %02x %s %02x\n", "   ", i, "\t\t " , 1);
       
     }
     else{
       fprintf(f, "%s %02x %s %02x\n", "   ", i, "\t\t " , i+2);
     }
     if(i == 200){
        printf("   Page   | Page Table Entry |\n");
        printf("------------------------------\n");
        printf("%s %02x %s %02x\n", "   ", i, "\t\t " , i+2);
     }
   }
   fflush(f);
}


