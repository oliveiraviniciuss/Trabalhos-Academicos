#include "Cache.h"

char* memory;
int max_memory_address;

//Prototipos

//Realiza a escrita na cache
static void writeAssociativeCache(Cache_Associative* cache, unsigned address, unsigned tag, int group_index, unsigned line_index, unsigned block_index, int *acessCounter);

//Função que procura por uma linha com a tag e guarda seu índice
bool searchGroup(int lines_perGroup, Group* group, int tag, int* line_index);

//Função que procura por um espaço disponível no conjunto
int searchBlankSpaceInGroup(int lines_perGroup, Group* group);

//Função que retorna a linha onde será substituída
int FIFO(int lines_perGroup, Group* group);

//Função que retorna a linha onde será substituída
int LRU(int lines_perGroup, Group* group);

//Função que aplica uma política de substituição e guarda o índice a ser substituído
void substitutionPolicy(int lines_perGroup, Group* group, int* line_index, int mode);

//Realiza a leitura de uma cache Associativa
char readAssociativeCache(Cache_Associative* cache, unsigned address, int policy, int* acess_counter);




//Funções

//Função que desaloca uma cache direta
void freeDirectCache(Cache_Direct* c)
{
	if (c == NULL)
		return;

	for (int i = 0; i < c->numLine; i ++)
	{
		if (c->lines + i != NULL)
			if (c->lines[i].block != NULL)
				free(c->lines[i].block);
	}

	free(c->lines);

	free(c);

	return;


}

//Função que desaloca uma cache Associativa
void freeAssociativeCache(Cache_Associative* c)
{

	if (c == NULL)
		return;

	for (int i = 0; i < c->groups_qtt; i ++)
	{
		for (int j = 0; j < c->numLine/c->groups_qtt; j ++)
		{
			if (c->groups[i].lines + j != NULL)
				if (c->groups[i].lines[j].block != NULL)
					free(c->groups[i].lines[j].block);
		}

		free(c->groups[i].lines);
	}

	free(c);

	return;
}

//Função que cria uma cache diretamente mapeada
Cache_Direct* newCacheDirectMapping(unsigned line_quant, unsigned block_size, char* mem)
{
	memory = mem;
	max_memory_address = strlen(memory);

	Cache_Direct* cache = NULL;

	unsigned i;

	//Aloca a memória
	memAlloc((void**) &cache, sizeof(Cache_Direct));

	//Armazena quantidade de linhas da cache
	cache->numLine = line_quant;

	//Guarda o tamanho do bloco
	cache->blockSize = block_size;

	//Realiza a alocação de cada linha do bloco
	memAlloc((void**) &(cache->lines), cache->numLine * sizeof(Line));

	//Inicialização padrão
	cache->isHit = false;
	cache->isMiss = false;
	cache->missCounter = 0;
	cache->hitCounter = 0;
	cache->size = cache->numLine * cache->blockSize;

	//Aloca, para cada linha, um bloco de tamanho já definido
	for(i = 0; i < cache->numLine; i++)
	{
		
		memAlloc((void **) &(cache->lines[i].block), cache->blockSize);
		
		//Inicialização padrão da linha
		cache->lines[i].tag = 0x00000000;
		cache->lines[i].isValid = false;
	}


	return cache;
}

//Função que Realiza Leiuras na Cache Associativa por modo
void counterReadAssociativeCache(Cache_Associative* cache, int policy, int mode)
{

	int acess_counter = 0;

	switch(mode)
	{

		case 1:
			//Sequencial
			for (unsigned i = 0; i < max_memory_address; i ++)
				readAssociativeCache(cache, i, policy, &acess_counter);

			break;

		case 2:
			//Aleatório
			for (unsigned i = 0; i < max_memory_address; i ++)
				readAssociativeCache(cache, (unsigned) rand() % max_memory_address, policy, &acess_counter);

			break;

	}

}

//Função que Realiza Leituras na Cache Direta por modo
void counterReadDirectCache(Cache_Direct* cache, int mode)
{

	int acess_counter = 0;

	switch(mode)
	{

		case 1:
			//Sequencial
			for (unsigned i = 0; i < max_memory_address; i ++)
				readDirectCache(cache, i);

			break;

		case 2:
			//Aleatório
			for (unsigned i = 0; i < max_memory_address; i ++)
				readDirectCache(cache, (unsigned) rand() % max_memory_address);

			break;

	}

}

//Função que imprime as informações da cache Associativa
void printAssociativeCacheInfo(Cache_Associative* cache)
{
	if (cache == NULL)
		return;

	double total_acess = (double) cache->missCounter + cache->hitCounter;

	printf("\n\tTamanho da Cache Associativa: %d bytes\n", cache->size);
	printf("\tTamanho de Bloco: %d bytes\n", cache->blockSize);
	printf("\tNúmero de Conjuntos: %d\n", cache->groups_qtt);
	printf("\tNúmero Total de Linhas: %d\n", cache->numLine);
	printf("\t* %u Misses - Miss Ratio ", cache->missCounter);

	if (total_acess == 0 ? printf("%d%%\n", 100) : printf("%0.2lf%%\n", (((double)cache->missCounter)/total_acess) * 100))
	
	printf("\t* %u Hits - Hit Ratio ", cache->hitCounter);

	if (total_acess == 0 ? printf("%d%%\n", 100) : printf("%0.2lf%%\n", 100 - (((double)cache->missCounter)/total_acess) * 100))
			


	return;

}

//Função que imprime as informações da cache Direta
void printDirectCacheInfo(Cache_Direct* cache)
{
	if (cache == NULL)
		return;

	double total_acess = (double) cache->missCounter + cache->hitCounter;

	printf("\n\tTamanho da Cache Direta: %d bytes\n", cache->size);
	printf("\tTamanho de Bloco: %d bytes\n", cache->blockSize);
	printf("\tNúmero Total de Linhas: %d\n", cache->numLine);
	printf("\t* %u Misses - Miss Ratio ", cache->missCounter);

	if (total_acess == 0 ? printf("%d%%\n", 100) : printf("%0.2lf%%\n", (((double)cache->missCounter)/total_acess) * 100))
	
	printf("\t* %u Hits - Hit Ratio ", cache->hitCounter);

	if (total_acess == 0 ? printf("%d%%\n", 100) : printf("%0.2lf%%\n", 100 - (((double)cache->missCounter)/total_acess) * 100))
			


	return;

}

//Função que imrpime os valores dentro da cache Associativa
void printAssociativeCache(Cache_Associative* c)
{

	if (c == NULL)
		return;

	for (int z = 0; z < c->groups_qtt; z++)
	{
		printf("\nConjunto %d:\n\n", z + 1);

		for (int i = 0; i < c->numLine/c->groups_qtt; i++)
		{
			printf("\tLinha %d (Dirtness %d | Frequência %d): ", i + 1, c->groups[z].lines[i].dirty, c->groups[z].lines[i].acess);

			for (int j = 0; j < c->blockSize; j ++)
			{
				printf("%c ", ((char*) c->groups[z].lines[i].block)[j]);
			}

			printf("\n");
		}
	
	}

	printf("\n");

	return;
}

//Função que imrpime os valores dentro da cache Direta
void printDirectCache(Cache_Direct* c)
{

	if (c == NULL)
		return;

	for (int z = 0; z < c->numLine; z++)
	{
		
		printf("\tLinha %d: ", z + 1);

		for (int j = 0; j < c->blockSize; j ++)
		{
			printf("%c ", ((char*) c->lines[z].block)[j]);
		}

		printf("\n");
	}
	

	printf("\n");

	return;
}

//Função que cria uma cache associativa
Cache_Associative* newCacheAssociativeMapping(unsigned line_perGroup, unsigned block_size, int groups, char* mem)
{
	memory = mem;
	max_memory_address = strlen(memory);

	Cache_Associative* cache = NULL;

	unsigned i;

	//Aloca memória para a cache
	memAlloc((void**) &cache, sizeof(Cache_Associative));

	//Calcula o número total de linhas
	cache->numLine = line_perGroup * groups;

	//Guarda o tamanho do bloco
	cache->blockSize = block_size;

	//Aloca memória para os grupos
	memAlloc((void**) &(cache->groups), groups * sizeof(Group));

	//Aloca memória para as linhas de cada grupo
	for (i = 0; i < groups; i ++)
		memAlloc((void**) &(((cache->groups)[i]).lines), line_perGroup * sizeof(Line));
	

	//Inicializa os valores padrão
	cache->isHit = false;
	cache->isMiss = false;
	cache->missCounter = 0;
	cache->hitCounter = 0;
	cache->size = cache->numLine * cache->blockSize;
	cache->groups_qtt = groups;

	//Realiza alocação de cada bloco em cada linha de cada grupo
	for(i = 0; i < groups; i++)
	{

		for (int j = 0; j < line_perGroup; j ++)
		{
			memAlloc((void**) &((cache->groups)[i].lines[j].block), block_size);

			//Inicializa de forma padrão
			cache->groups[i].lines[j].isValid = false;
			cache->groups[i].lines[j].tag = 0;
		}
		
		
	}


	return cache;
}

//Função que aloca memória alinhada
void memAlloc(void ** info, int size)
{
	if (posix_memalign(info, 64, size))
	{
		printf("Erro de alocação");
		exit(2);
	}

	return;
}

//Função que procura por uma linha com a tag em um grupo e guarda seu índice
bool searchGroup(int lines_perGroup, Group* group, int tag, int* line_index)
{
	//Percorre as linhas do grupo
	for (int i = 0; i < lines_perGroup; i ++)
	{
		//Se válido e se a tag da linha é igual a tag procurada
		if (group->lines[i].isValid == true && tag == group->lines[i].tag)
		{
			*line_index = i;
			return true;
		}
	}

	return false;
}

//Função que retorna a linha onde será substituída, no grupo
int FIFO(int lines_perGroup, Group* group)
{

	int line_index = 0;

	//Percorre as linhas do grupo
	for (int i = 0; i < lines_perGroup; i ++)
	{
		//Grava o índice da linha que foi escrita no acesso mais cedo
		if (group->lines[i].dirty < group->lines[line_index].dirty)
			line_index = i;
	}

	return line_index;
}

//Função que procura por um espaço disponível no conjunto
int searchBlankSpaceInGroup(int lines_perGroup, Group* group)
{

	//Percorre as linhas verificando sua validade e retorna seu índice
	for (int i = 0; i < lines_perGroup; i ++)
	{
		if (group->lines[i].isValid == false)
			return i;
	}

	return -1;
}

//Função que retorna a linha onde será substituída, no grupo
int LRU(int lines_perGroup, Group* group)
{

	int line_index = 0;

	//Percorre as linhas
	for (int i = 0; i < lines_perGroup; i ++)
	{
		//Grava o índice da linha que teve menos acessos
		if (group->lines[i].acess < group->lines[line_index].acess)
			line_index = i;
	}

	return line_index;
}

//Função que aplica uma política de substituição e guarda o índice a ser substituído
void substitutionPolicy(int lines_perGroup, Group* group, int* line_index, int mode)
{

	switch(mode)
	{
		case 0:
			///FIFO
			*line_index = FIFO(lines_perGroup, group);
			break;
		case 1:
			//LRU
			*line_index = LRU(lines_perGroup, group);
			break;
		default:
			assert(mode);

		break;
	}

}


//Realiza a leitura de uma cache Associativa
char readAssociativeCache(Cache_Associative* cache, unsigned address, int policy, int* acess_counter)
{
	//Verifica a Cache
	if (cache == NULL || (policy != 0 && policy != 1))		//0 Fifo, 1 LRU
		exit(1);

	//Armazena o índice no bloco, tag e índice do grupo
	unsigned index, tag, group_index;

	//Armazena o índice da linha
	int line_index = 0;

	//Armazena o número de linhas por grupo
	unsigned lines_perGroup = (unsigned) cache->numLine/cache->groups_qtt;

	//Número de bits para o índice do bloco
	unsigned index_bits = (unsigned) log2(cache->blockSize);

	//Número de bits para o índice do grupo
	unsigned group_index_bits = (unsigned) log2(cache->groups_qtt);

	//Número de bits para tag
	unsigned tag_bits = ADRESS_SIZE - index_bits - group_index_bits;

	//Calcula o índice do bloco
	//index = address & ((unsigned) pow(2, index_bits) - 1); 
	index = getLSB(address, index_bits);

	//Calcula o índice do grupo ***************
	group_index = (address & ((cache->groups_qtt - 1) << (index_bits))) >> index_bits;
	

	//Calcula a tag
	tag = (address & (((unsigned) ( pow(2, tag_bits) - 1)  << (group_index_bits + index_bits)))) >> (group_index_bits + index_bits);


	//Procura no Grupo por  um índice que contenha a informação
	if (searchGroup(lines_perGroup, &(cache->groups[group_index]), tag, &line_index))
	{
		//Ativa o hit
		cache->isHit = true;

		//Desativa o hit
		cache->isMiss = false;

		//Incrementa o contador de hit
		cache->hitCounter ++;

		//Incrementa o acesso
		cache->groups[group_index].lines[line_index].acess ++;

	}
	//Cache Miss
	else
	{

		//Desativa o hit
		cache->isHit = false;
		
		//Ativa o miss
		cache->isMiss = true;

		//Procura por um espaço invalidado no grupo para entrar o novo bloco
		line_index = searchBlankSpaceInGroup(lines_perGroup, &(cache->groups[group_index]));

		//Se não achou um espaço para utilizar, o Grupo está cheio
		if (line_index < 0)
			substitutionPolicy(lines_perGroup, &(cache->groups[group_index]), &line_index, policy);

		//Escreve a informação na cache
		writeAssociativeCache(cache, address, tag, group_index, line_index, index, acess_counter);

		//Incrementa o contador de miss
		cache->missCounter ++;

	}


	//Retorna a informação requerida
	return ((char*) (cache->groups[group_index].lines[line_index].block))[index];
}

//Realiza a leitura de uma cache diretamente mapeada
char readDirectCache(Cache_Direct* cache, unsigned address)
{
	//Verifica a cache
	if (cache == NULL)
		exit(1);

	unsigned index, tag, line_index;

	//Armazena quantidade de bits para o bloco
	unsigned index_bits = (unsigned) log2(cache->blockSize);

	//Armazena quantidade de bits para a linha
	unsigned line_index_bits = (unsigned) log(cache->numLine);

	//Armazena quantidade de bits para a tag
	unsigned tag_bits = ADRESS_SIZE - index_bits - line_index_bits;

	//Calcula o índice
	//index = address & ((unsigned) pow(2, index_bits) - 1); 
	index = getLSB(address, index_bits);

	//Calcula o índice da linha
	line_index = (address & ((cache->numLine - 1) << (index_bits))) >> index_bits;

	//Calcula a tag 
	tag = (address & (((unsigned) ( pow(2, tag_bits) - 1)  << (line_index_bits + index_bits)))) >> (line_index_bits + index_bits);

	//Se a linha é válida e a tag é a mesma
	if (cache->lines[line_index].isValid == true && cache->lines[line_index].tag == tag)
	{
		//Ativa  o Hit
		cache->isHit = true;

		//Desativa o Miss
		cache->isMiss = false;

		//Incrementa  o contador
		cache->hitCounter ++;

	}
	//A informação contida não é a requerida
	else
	{

		//Desativa o Hit
		cache->isHit = false;
		
		//Ativa o Miss
		cache->isMiss = true;

		//Escreve na Cache
		writeDirectCache(cache, address, tag, line_index, index);

		//Incrementa o contador
		cache->missCounter ++;

	}


	//Returns the required info
	return ((char*) (cache->lines[line_index].block))[index];
}

//Realiza a escrita na cache
static void writeAssociativeCache(Cache_Associative* cache, unsigned address, unsigned tag, int group_index, unsigned line_index, unsigned block_index, int *acessCounter)
{

	//Realiza a cópia
	for (int i = 0; i < cache->blockSize; i ++)
	{
		//Se tenta acessar fora do bloco ou passar do endereço máximo de memória
		if (i + block_index >= cache->blockSize || i + address > max_memory_address)
			break;

		((char*) cache->groups[group_index].lines[line_index].block)[i + block_index] = memory[i + address];
	}
	
	//Grava a tag, o número do acesso, e valida a linha
	cache->groups[group_index].lines[line_index].tag = tag;
	cache->groups[group_index].lines[line_index].dirty = *acessCounter;
	cache->groups[group_index].lines[line_index].acess = 0;
	cache->groups[group_index].lines[line_index].isValid = true;

	//Incrementa o número do acesso
	*acessCounter = *acessCounter + 1;

	return;
}

//Escreve em uma cache direta
void writeDirectCache(Cache_Direct* c, unsigned address, unsigned tag, unsigned line_index, unsigned block_index)
{
	//Verifica a cache
	if (c == NULL)
		return;

	//Atualiza a tag
	c->lines[line_index].tag = tag;

	//Copia os dados
	for (int i = 0; i < c->blockSize; i ++)
	{
		//Não copia se ultrapassar o bloco ou a memória
		if ((i + address) > max_memory_address || (i + block_index) > c->blockSize)
			break;

		
		((char*) c->lines[line_index].block)[i + block_index] = memory[i + address];
	}

	//Ativa a validade da linha
	c->lines[line_index].isValid = true;

	return;
}