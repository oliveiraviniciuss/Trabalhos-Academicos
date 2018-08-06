#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define log2(x) (log((x))/log(2))
#define getLSB(y, x) ((unsigned)y & ((unsigned) pow(2, x) - 1))

//Tamanho do endereço de memória é 32 bits
#define ADRESS_SIZE 32

//Estruturas
typedef struct Line
{
	void* block;
	unsigned tag;
	bool isValid;
	unsigned dirty;	//Número do acesso (Tempo)
	unsigned acess;	//Numero de acessos (frequencia)
}Line;

typedef struct group
{
	Line* lines;
}Group;

typedef struct cache_associative
{
    Group* groups;
	unsigned blockSize;
	unsigned numLine;
	bool isHit;
	bool isMiss;
	unsigned missCounter;
	unsigned hitCounter;	
	unsigned size;
	unsigned groups_qtt;

}Cache_Associative;

typedef struct cache_direct
{
    Line* lines;
	unsigned blockSize;
	unsigned numLine;
	bool isHit;
	bool isMiss;
	unsigned missCounter;
	unsigned hitCounter;	
	unsigned size;

}Cache_Direct;


//Função que imprime as informações da cache
void printAssociativeCacheInfo(Cache_Associative* cache);

//Função que imrpime os valores dentro da cache
void printAssociativeCache(Cache_Associative* cache);

//Função que aloca memória alinhada
void memAlloc(void ** info, int size);

//Função que cria uma cache associativa
Cache_Associative* newCacheAssociativeMapping(unsigned line_perGroup, unsigned block_size, int groups, char* mem);

//Função que Realiza Leiuras na Cache por modo
void counterReadAssociativeCache(Cache_Associative* cache, int policy, int mode);

//Realiza a leitura de uma cache diretamente mapeada
char readDirectCache(Cache_Direct* cache, unsigned address);

//Função que cria uma cache diretamente mapeada
Cache_Direct* newCacheDirectMapping(unsigned line_quant, unsigned block_size, char* mem);

//Função que Realiza Leituras na Cache Direta por modo
void counterReadDirectCache(Cache_Direct* cache, int mode);

//Escreve em uma cache direta
void writeDirectCache(Cache_Direct* c, unsigned address, unsigned tag, unsigned line_index, unsigned block_index);

//Função que imprime as informações da cache Direta
void printDirectCacheInfo(Cache_Direct* cache);

//Função que imrpime os valores dentro da cache Direta
void printDirectCache(Cache_Direct* c);

//Função que desaloca uma cache direta
void freeDirectCache(Cache_Direct* c);

//Função que desaloca uma cache Associativa
void freeAssociativeCache(Cache_Associative* c);




