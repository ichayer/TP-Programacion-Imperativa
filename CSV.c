#include <stdio.h>
#include "cityADT.h"


int main(int argc, char const *argv[])   
{
    if(argc>3)
    {
        fprintf(stderr,"Invalid amount of arguments"); /* esto nose si esta bien, hay que separar front de back */
        return 1;
    }

   FILE * fp = fopen(argv[1] , "r");
   FILE * fp2= fopen(argv[2], "r");
   if(fp == NULL || fp2 == NULL) 
   {
      fprintf(stderr,"Error opening file");
      return 1;
   }

    fclose(fp); fclose(fp2);
    return 0;
}

