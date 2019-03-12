#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

#define allocated 65536


unsigned short* allocateMemory(){

 unsigned short *mem;
 mem  =  (unsigned short*)malloc(sizeof(allocated));
 return mem;
}
