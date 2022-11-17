#include "simulador.h"

int main(int argc, char * argv[])
{
  int page_size, mem_size, n_pages, page_id, n_page_faults, page_ids_size;
  int alg_type = -1; // -1 -> invalido, 0 -> LRU, 1 -> NRU
  Page *pages;
  int *page_ids;
  int time = 0;
  FILE *arq;
  unsigned int addr;
  char rw;
  
  if (argc < 4)
  {
    puts("4 argumentos necessarios");
    exit(0);
  }

  if (strcmp(argv[1], "LRU") == 0)
  {
    alg_type = 0;
  }

  if (strcmp(argv[1], "NRU") == 0)
  {
    alg_type = 1;
  }
  
  if (alg_type == -1)
  {
    perror("Algoritmo invalido, apenas LRU e NRU sao validos");
    exit(1);
  }
  
  arq = fopen(argv[2], "r");
  
  if (arq == NULL)
  {
    perror("arquivo de log nao encontrado");
    exit(2);
  }
  
  if (8 > atoi(argv[3]) || atoi(argv[3]) > 32)
  {
    perror("tamanho de pagina invalido, deve ser entre 8 e 32");
    exit(3);
  }

  if (1 > atoi(argv[4]) || atoi(argv[4]) > 16)
  {
    perror("tamanho de memoria fisica invalido, deve ser entre 1 e 16");
    exit(4);
  }

  arq = fopen(argv[2], "r");
  page_size = atoi(argv[3]);
  mem_size = atoi(argv[4]);
  int cycle_num =0;
  int num_of_trades = 0;
  n_pages = (page_size * 1000)/mem_size;

  pages = (Page *) malloc(sizeof(Page) * n_pages);
  //page_ids = (int *) malloc(sizeof(Page) * n_pages)
  
  if (pages == NULL)
  {
    perror("erro no malloc");
    exit(5);
  }
  int flag = 0;
  while(fscanf(arq, "%x %c ", &addr, &rw) == 2)
  {
      flag = 0;
      for (int i = 0; i < n_pages; i++)
      {
        page_id = indice_pagina(addr, page_size);
        
        if (pages[i].id == page_id)
        {
          pages[i].t_last_access = time;
          time++;
          flag = 1;
          break;
        }
        
      }
    if(flag!=1){
      if (alg_type == 0)
          {
            int index_to_overwrite = lru(pages,page_id,n_pages);
            pages[index_to_overwrite].id = page_id;
            pages[index_to_overwrite].M = 0;
            pages[index_to_overwrite].R = 0;
            pages[index_to_overwrite].t_last_access = cycle_num;
            num_of_trades++;
          }
          else
          {
            nru(pages,page_id);
          }
          time++;
          n_page_faults++;
    }
    cycle_num++;
  }
  printf("Numero de trocas: %d\n",num_of_trades);
  printf("Paginas escritas: %d\n",cycle_num - num_of_trades);
  return 0;
}

