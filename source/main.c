#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/funcoes-gerais.h"
#include "../include/linha.h"
#include "../include/veiculo.h"
//#include <linha.h> em comentario por enquanto
//#include <veiculo.h> em comentario por enquanto

/*
            TRABALHO DESENVOLVIDO PARA A DISCIPLINA SCC-0215 ORGANIZACAO DE ARQUIVOS
            
    INTEGRANTES:
        ANTONIO RODRIGUES RIGOLINO - 11795791
        MATHEUS VENTURA DE SOUSA - 11345541

*/
int main(){
  int num_func;			        //indica qual funcionalidade sera pedida do programa
  scanf("%d",&num_func);

  char filenamesrc[50] = "\0";
  char filenamedest[50] = "\0";
  char tmp[50] = "\0";

  s_file_t *filesrc = NULL, *filedest = NULL;
  db_t *db = NULL, *searchResult = NULL;
  header_t *header = NULL;
  int nRegistros = 0;

  char searchfieldname[30] = "\0";
  char find_key[100] = "\0";

  strcpy(tmp, FILEPATH);

  switch (num_func){             //para melhor eficiencia usa-se um switch
    case 1:
    {
      char filenamecsv[20];
      char filenamebin[20];
      scanf("%s %s", filenamecsv, filenamebin);
      scanf("%*c");
      printf("file csv: %s\nfile bin: %s\n", filenamecsv, filenamebin);
      // writeBin - parâmetros:
      // - nome de um arquivo CSV com o formato especificado já existente, ou seja, modo "r"
      // - nome para um arquivo binário que será gerado a partir desse csv, ou seja, modo "wb+", o + é necessário para manipulações no header
      writeBin(filenamecsv, filenamebin);
      break;
    }
    case 2:
      // Manipulação de string do caminho do arquivo origem
      scanf("%s", filenamesrc);
      
      filesrc = openfile(filenamesrc, "r");
      if(filesrc != NULL){
        // readDBfromCSV - parâmetros: 
        //  - ponteiro da struct que contém o arquivo origem
        //  - número de registros: para indicar o infinito, foi usado o nº: 10000000
        db = readDBfromCSV(filesrc, 10000000);

        closefile(filesrc);

        // Manipulação de string do caminho do arquivo destino
        scanf("%s", filenamedest);
        
        filedest = openfile(filenamedest, "wb");

        if(filedest != NULL){
          // Escreve o db no arquivo destino.
          writeDB(filedest, db, 0);

          closefile(filedest);

          binarioNaTela(filenamedest);      
        }
      }
      break;
    case 3:
    {
      char filenamebin[20];
      scanf("%s", filenamebin);
      scanf("%*c");
      //printBin - parâmetros
      // - nome do arquivo binário (JÁ EXISTENTE) que terá seus conteúdos lidos e será impresso, ou seja, modo "rb".          
      printBin(filenamebin);
      break;
    }
    case 4:
      // Manipulação de string do caminho do arquivo origem
      scanf("%s", filenamesrc);
      
      filesrc = openfile(filenamesrc, "rb");

      if(filesrc != NULL){  
        db = readDBfromBIN(filesrc);

        closefile(filesrc);

        // mostra na tela todos os registros encontrados no arquivo destino com exceção dos excluidos
        printSearchResult(db);
      }
      break;
    case 5:
    {
      char filenamebin[20];
      char campo[50];
      scanf("%s", filenamebin);
      scanf("%*c");
      scanf("%s", campo);
      scanf("%*c");
      // searchPrint - parâmetros:
      // - nome de um arquivo binário no qual já estão contidos os registros, ou seja, modo "rb"
      // - string que define o campo procurado. O valor do campo será coletado dentro da função
      searchPrint(filenamebin, campo);
      break;
    }
    case 6:
      // Manipulação de string do caminho do arquivo origem
      scanf("%s", filenamesrc);
      
      filesrc = openfile(filenamesrc, "rb");

      if(filesrc != NULL){
        db = readDBfromBIN(filesrc);

        closefile(filesrc);

        fgetc(stdin);
        scanf("%s ", searchfieldname);
        scan_quote_string(find_key);

        // procura o campo desejado
        searchResult = searchAttrib(db, searchfieldname, find_key);
        if(searchResult != NULL) searchResult->header = db->header;

        // Mostra na tela todos os resultados encontrados, com exceção dos removidos
        printSearchResult(searchResult);
      }
      break;
    case 7:
    {
      char filenamebin[20];
      int num_inserts;
      scanf("%s %d", filenamebin, &num_inserts);
      scanf("%*c");
      // insert_num_reg - parâmetros:
      // - número de inserções que serão realizadas
      // - nome do arquivo binário já existente que será o destino das inserções, ou seja, modo "rb+" pois o arquivo já existe e precisamos ler E escrever.
      insert_num_reg(num_inserts, filenamebin);
      break;
    }
    case 8:
      // Manipulação de string do caminho do arquivo destino
      scanf("%s", filenamedest);
      
      scanf("%d", &nRegistros);
      fgetc(stdin);

      filedest = openfile(filenamedest, "rb+");

      if(filedest != NULL){
        // posiciona o ponteiro do arquivo para depois do status
        fseek(filedest->fp, 1, SEEK_SET);
        header = readHeaderfromBIN(filedest);

        db = readDBfromStdin(nRegistros, header);

        header = NULL;

        // posiciona o ponteiro no início do arquivo
        fseek(filedest->fp, 0, SEEK_SET);
        writeDB(filedest, db, 1);

        closefile(filedest);

        binarioNaTela(filenamedest);
      }
      break;
    default:
      printf ("ERRO CODIGO DA FUNCIONALIDADE INVALIDO!\n");         //codigo da funcionalidade fora do escopo
      break;
    }

  return 0;
}
