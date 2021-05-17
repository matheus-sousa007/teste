#include "../include/veiculo.h"
<<<<<<< HEAD
#include "../include/funcoes-gerais.h"
=======
>>>>>>> 2c32aa271e75c3b4b0ce052cddc80572829d1476

typedef struct header{
    char status;
    int64_t byteProxReg;
    int nroRegistros;
    int nroRegRemovidos;
    char descrevePrefixo[18];
    char descreveData[35];
    char descreveLugares[42];
    char descreveLinha[26];
    char descreveModelo[17];
    char descreveCategoria[20];
}header_t;

typedef struct dataReg{
    char removido;
    int tamRegistro;
    char prefixo[5];
    char data[10];
    int quantidadeLugares;
    int codLinha;
    int tamModelo;
    char modelo[50]; // Tamanho Variavel
    int tamCategoria;
    char categoria[50]; // Tamanho Variável
}dataReg_t;

typedef struct db{
    dataReg_t *db;
<<<<<<< HEAD
}db_t;

header_t *readHeader(s_file_t *dataFile){
    // Verifica se há ponteiro para o arquivo
    if(dataFile->fp == NULL){
        printf("Arquivo inexistente!\n");
        return NULL;
    }
    if(dataFile->EmptyFile == "1"){
        printf("Arquivo vazio!\n");
        return NULL;
    }   
}
=======
}db_t;
>>>>>>> 2c32aa271e75c3b4b0ce052cddc80572829d1476
