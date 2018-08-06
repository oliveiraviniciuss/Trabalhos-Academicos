#include "mymalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>

//Tamanho em bytes do bloco
#define T_BLOCK_SIZE sizeof(struct s_block)

///////////////////////////////////////////////////////////////////

/*Uma estrutura de uma alocação de memória
guarda um ponteiro para próxima alocação do programa,informações do bloco
como tamanho, estado (liberado ou não) e quantidade pedida*/

//Estrutura de uma alocação
typedef struct s_block *t_block;

struct s_block
{
	t_block	next;	
	unsigned asked;
	unsigned free;
	unsigned size;
	
};

///////////////////////////////////////////////////////////////////

//Base da Heap
void* heap_base = NULL;

//Lita encadeada de alocações
t_block blockList = NULL;

//Constante do tamanho da heap
long long unsigned static heap_end;

//Se já foi inicido
bool mymalloc_initialized = false;

///////////////////////////////////////////////////////////////////

//Protótipos
//Procura por um bloco disponível (First fit)
void* FindBlock(long long unsigned size);
unsigned MyMallocStructSize();

///////////////////////////////////////////////////////////////////

//Funções

//Init
int MyMallocInit(long long unsigned size)
{

	//Flag de retorno
	int flag = -1;

	//Se já foi iniciado retorna um erro 
	if (mymalloc_initialized == true)
		flag = 0;

	else
	{
		//Pega o endereço base da heap de tamanho size
		heap_base = sbrk(0);

		//Verifica se foi possível extender o segmento de dados
		heap_base = sbrk(size);

		/*sbrk() dispara um erro na biblioteca errno.h
		a qual existe uma variável errno que guarda o 
		indentificador do erro em caso de falha e a função 
		perror() efetua o disparo do erro ou do sucesso na 
		tela, onde __FUNCTION__ é o nome da função (MyMallocinit)*/

		//Verifica erro ou sucesso
		if (errno)
		{
			//Dispara erro
			perror(__FUNCTION__);

			//Ativa flag de erro
			flag = 0;
		}
		else
		{
			//Ativa o fucnionamento
			mymalloc_initialized = true;

			/*Endereço de fim da heap é a base fornecida
			mais o tamanho requerido do usuário mais uma 
			estrutura de pelo menos uma alocação futura*/

			//Define o fim da heap
			heap_end = heap_base + size;
		}
		
	}
	
	return flag;
}

//Função que retorna o tamanho da estrutura
unsigned MyMallocStructSize()
{
	return T_BLOCK_SIZE;
}

void* MyMalloc(long long unsigned size)
{
	if (!mymalloc_initialized)
		return NULL;

	//Bloco requerido pelo usuário
	t_block block = FindBlock(size);

	//Quantidade pedida
	block->asked = (unsigned) size;

	//Retorna o bloco com um deslocmento da estrutura
	//Devolve o usuário apenas o endereço que ele utilizará de fato
	return (block+1);

}

//Procura por um bloco disponível (First fit)
void* FindBlock(long long unsigned size)
{
	//Bloco a ser retornado
	t_block block = NULL;

	//Primeira alocação
	if ((blockList == NULL) && (heap_base + T_BLOCK_SIZE + size ) <= heap_end)
	{

		/*Bloco é um endereço, que contém uma estrutura t_block
		e após a esturua começa o endereço a ser usado pelo usuário*/

		//Cria um bloco
		block = heap_base;

		//Alinha o primeiro bloco com a heap
		*((t_block)heap_base) = *block;


		//Atualiza o estado do bloco
		block->free = 0;

		//Adiciona o tamanho requerido ao bloco
		block->size = size;

		//Atualiza o ponteiro para a próxima alocação
		block->next = NULL;

		//Atualiza a base da heap
		heap_base += (block->size + T_BLOCK_SIZE);

		//Adiciona o bloco ao encadeamento
		blockList = block;

	}
	//Segunda alocação em diante
	else
	{
		//Armazenamento temporário dos blocos encadeados
		t_block aux = blockList;

		//Enquanto o bloco atual tiver um próximo
		while (aux->next != NULL)
		{
			//Se o bloco atual está liberado e se seu tamanho é maior
			//que o requerido
			if ((aux->free == 1) && (aux->size >= size))
				break;

			//Continua percorrendo
			aux = aux->next;
		}


		//Se achou um bloco que se encaixa
		if (aux->next != NULL || (aux->free == 1 && aux->size >= size))
		{
		
			//Retira o free
			aux->free = 0;

			//Guarda o bloco a ser retornado
			block = aux;

		}
		//Se entre a última alocação e o fim da heap tem espaço
		else if ((heap_base + T_BLOCK_SIZE + size ) <= heap_end)
		{
			if (aux == NULL)
				exit(2);


			//Cria bloco
			block = heap_base;

			//Alinha a heap com o bloco
		    *((t_block)heap_base) = *block;

		  
		      //Atualiza o estado do bloco
		    block->free = 0;

		    //Adiciona o tamanho requerido ao bloco
		    block->size = size;

			//Atualiza o ponteiro para a próxima alocação
			block->next = NULL;
				
			//encadeia o bloco
			aux->next = block;


		    //Atualiza a base da heap
			heap_base += (block->size + T_BLOCK_SIZE);

			
		}
	}
	
	return block;
}

//Desalocação de memória
int MyMallocFree(void *ptr)
{

	//Cast do endereço fornecido pelo usuário para a estrutura
	t_block block = (t_block) ptr;

	//Decrementa o endereço para acessar a estrutura
	block -= 1;

	//Atualiza o estado do bloco
	block->free = 1;

}

void MyMallocGerency()
{	
	//Se não foi utilizado, não pode executar
	if (!mymalloc_initialized)
	{
		printf("Management Failed! Not Initialzed!\n");
		exit(1);
	}

	//Infos
	unsigned allocations = 0, deallocations = 0, total_bytes = 0, remaining_bytes = 0,
		blocks = 0, maximum_fragment = 0, free_space = 0, tot_heap = 0, internal_fragment = 0,
		tot_internal_frag = 0;

	float all_average = 0, all_percent, free_percent, deall_average = 0;

	printf("\n\n\t******MANAGEMENT******\n\n");

	printf("HEAP:\tStart Address ~ ");

	//Se não há blocos a heap começa no heap_base
	if (blockList == NULL)
	{
		tot_heap = heap_end - (long long unsigned) heap_base;
		printf("%Lu\n", heap_base);
	}
	//A heap começa no primeiro elemento
	else
	{
		tot_heap = heap_end - (long long unsigned) blockList;
		printf("%Lu\n", (long long unsigned) blockList);
	}

	printf("\tEnd Address ~ %Lu\n", heap_end);
	printf("\tTotal Heap Size ~ %Lu bytes\n\n", tot_heap);

	//Calcula as informações
	for (t_block aux = blockList; aux != NULL; aux = aux->next)
	{
		if (aux->free == 1)
		{
			deallocations ++;
			remaining_bytes += aux->size;
			blocks ++;

			if (aux->size > maximum_fragment)
				maximum_fragment = aux->size;
		}
		else
		{
			allocations ++;
			total_bytes += aux->size;
			blocks ++;
		}

		if (aux->free == 0)
			tot_internal_frag += aux->size - aux->asked;

		if (aux->size < aux->asked)
			printf("error\n");

		if (aux->free == 0 && (aux->size - aux->asked) > internal_fragment)
			internal_fragment = (aux->size - aux->asked);

		if (aux->next == NULL)
			free_space += remaining_bytes + (heap_end - ((long long unsigned)aux + aux->size + T_BLOCK_SIZE));
	}


	if (deallocations)
		deall_average = (float) remaining_bytes/deallocations;

	if (allocations)
		all_average = (float) ((total_bytes)/allocations);

	if (!blocks)
		free_space = tot_heap;

	all_percent = (float) (100*(total_bytes + allocations*T_BLOCK_SIZE)/(tot_heap));

	free_percent = (float) (free_space*100)/(tot_heap);


	printf("ALLOC.:\tTotal Allocations ~ %Lu\n", allocations);
	printf("\tTotal Allocated Bytes ~ %Lu bytes (%0.2f%)\n", total_bytes, (float) (total_bytes*100)/tot_heap);
	printf("\tTotal Allocated Bytes W/ Strucutres ~ %Lu bytes(%0.2f%)\n", total_bytes + allocations*T_BLOCK_SIZE, all_percent );
	printf("\tAllocation Average ~ %0.2f bytes\n", all_average );
	printf("\tStructure Size ~ %Lu bytes\n", T_BLOCK_SIZE);
	printf("\n\tTotal Deallocated Blocks ~ %Lu\n", deallocations);
	printf("\tTotal Deallocated Bytes ~ %Lu bytes (%0.2f%)\n", remaining_bytes, deall_average);
	printf("\tDeallocation Average ~ %0.2f bytes\n", deall_average);
	printf("\tMaximum External Fragment ~ %Lu bytes (%0.2f%)\n", maximum_fragment, (float) maximum_fragment/(tot_heap));
	printf("\tTotal Internal Fragment ~ %Lu bytes (%0.2f%)\n", tot_internal_frag, (float) (tot_internal_frag/tot_heap)*100);
	printf("\tMaximum Internal Fragment ~ %Lu bytes (%0.2f%)\n", internal_fragment, (float) internal_fragment/tot_heap);
	printf("\tReal Free Space ~ %Lu bytes(%0.2f%)\n", free_space, free_percent);

}




