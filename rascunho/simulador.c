// Eduardo Dantas Luna, 2111484
// Ricardo Bastos Leta Vieira, 2110526

#include "simulador.h"

int main(int argc, char * argv[])
{
  int page_size, mem_size, n_pages, page_id, n_page_faults, page_ids_size;
  int index_to_overwrite;
  int alg_type = -1; // -1 -> invalido, 0 -> LRU, 1 -> NRU
  Page *pages;
  int pages_current_size = 0;
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
    page_ids = page_ids_arr(n_pages);
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
  n_pages = (page_size * 1000)/ mem_size;
  pages = (Page *) malloc(sizeof(Page) * n_pages);
  //page_ids = (int *) malloc(sizeof(Page) * n_pages)
  printf("Numero de max de paginas em memoria: %d\n",n_pages);
  
  if (pages == NULL)
  {
    perror("erro no malloc");
    exit(5);
  }
  
  while(fscanf(arq, "%x %c ", &addr, &rw) == 2)
  {
      page_id = get_indice_pagina(addr, page_size);

      if(!is_in_Pages(pages,page_id,pages_current_size))
      {  
        if(pages_current_size >= n_pages)
        {
          if (alg_type == 0)
          {
            index_to_overwrite = lru(pages,page_id,n_pages);
            set_page(pages,index_to_overwrite,page_id,time, rw);
            // page_ids[pages_current_size] = index_to_overwrite;
            // n_page_faults++;
            // pages_current_size++;
          }
          else if(alg_type == 1)
          {
            index_to_overwrite = nru(pages,page_ids,n_pages);
            set_page(pages,index_to_overwrite,page_id,time, rw);
            page_ids[pages_current_size] = index_to_overwrite;
          }
      } 
      else 
      {
        set_page(pages,pages_current_size,page_id,time, rw);
        page_ids[pages_current_size] = page_id;
        pages_current_size++;
      }
        
      n_page_faults++;
    }
    time++;
  }

  printf("Page Faults: %d \n",n_page_faults);
  return 0;
}

