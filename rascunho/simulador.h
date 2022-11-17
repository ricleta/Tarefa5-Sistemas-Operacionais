#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _page
{
  int R;
  int M;
  int t_last_access;
  int id;
} Page;

int indice_pagina(int endereco,int paginaTamanho)
{
  int res;
  paginaTamanho *= 1000;
  res = (int) ceil(log2(paginaTamanho));
  return endereco >> res;
}


int lru(Page * pages,int page_id,int pages_size)
{
  int min_id = 0;
  int min_t = pages->id;
  
  for(int i = 0; i < pages_size ; i++){
    
  }
}

int nru(Page * pages,int page_id)
{
    
}