
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

int randomNum();
unsigned short allocateMemory();
int randomAscii();

int main() {

   //unsigned short *mem;
   //mem = allocateMemory();
   unsigned short *mem;
   mem  =  (unsigned short*)malloc(sizeof(allocated));

   if(mem == NULL){
       printf("couldnt allocate memory\n");
   }
   else{
       printf("Memory allocation sucessfull\n");
   }


   int num = randomNum();
   int ranAscii = randomAscii(mem,num);

   return 0;
}

int randomNum(){
   // Randomly get between 2048 and 20480 bytes
   srand(time(0));
   int assigned = rand() % (max- min + 1) + min;
   printf("%d\n", assigned);
   return assigned;
}

int randomAscii(unsigned short *mem,int num){
   // Randomly create a number between 33 and 126
   srand(time(0));
   // populate memory array with characters
   for(int i = memMin; i < num ; i ++){
      int asciiNum = rand() % (maxAscii- minAscii + 1) + minAscii;
      char c = asciiNum;
      printf("%c",c);
      mem[i]=c;
   } \
   int asciiNum = rand() % (maxAscii- minAscii + 1) + minAscii;
   printf("%d\n", asciiNum);
   return asciiNum;
}

//unsigned short alllocateMemory(){

//  unsigned short *mem; 
//    mem  =  (unsigned short*)malloc(sizeof(allocated));

 //   if(mem == NULL){
//        printf("couldnt allocate memory\n");
 //   }
 //   else{
  //      printf("Memory allocation sucessfull\n");
  //  }
 //   return mem;

//}
