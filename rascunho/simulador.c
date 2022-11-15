#include "simulador.h"

int main(int argc, char * argv[])
{
  if (argc < 4)
  {
    puts("4 argumentos necessarios");
    exit(0);
  }

  int n_paginas = 0;
  MEM *log_addr;
  
  // printf("./simulador %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
  if (strcmp(argv[1], "LRU") == 0)
  {
    log_addr = (MEM *) malloc(sizeof(MEM) * n_paginas);
    printf("LRU\n");
  }
  else if (strcmp(argv[1], "NRU") == 0)
  {
    log_addr = (MEM *) malloc(sizeof(MEM) * n_paginas);
    printf("NRU\n");
  }
  
  FILE *arq = fopen(argv[2], "r");
  unsigned int addr;
  char rw;
  int page = 0;
  int s = 13; // para pag de 8k e mem fisica de 16 M
  
  while(fscanf(arq, "%x %c ", &addr, &rw) == 2)
    {
      page = addr >> s;
      
      // printf("%x\n", page);
      
      // printf("%x %c\n", addr, rw);
    }
  
  return 0;
}