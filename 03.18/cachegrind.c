#define size 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int array[size][size] = {};
    int i = 0, j = 0;
    for(;i < size; i++)
      for(;j < size; j++){
        array[i][j] = rand() % 2;
      }
   int sum = 0;
   for(i = 0; i < size; i++)
      for(j = 0; j < size; j++){
        if(!strncmp("-ij", argv[1], 3))
            sum += array[i][j];
          else
            sum += array[j][i];
      }

  printf("sum = %d\n", sum);
  return 0;
}
