#ifndef FUNCOESGERAIS_H_
#define FUNCOESGERAIS_H_

#include<stdio.h>
#include<stdlib.h>

typedef struct s_file{
    FILE *fp;
    char EmptyFile;
}s_file_t;

void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);
s_file_t *openfile(char *filename, char *openmode);


#endif