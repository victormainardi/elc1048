#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);
void tarefa_2(void);
void tarefa_3(void);
/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)


//exercício 3   tamanho do buffer a ser lido/escrito
#define TAM 10
//buffer preenchido / consumido pelas thread
int buffer[TAM];

semaforo_t mutex = {1, 0};
semaforo_t vazio = {TAM, 0};
semaforo_t cheio = {0, 0};




//funcao produtor
/*
void* produtor(void* arg){
  while(1){
    if(buf_cheio == 0){
      //lock mutex
      pthread_mutex_lock(&mutex);
      printf("PRODUZINDO!: ");
      //enchendo buffer com funcao rand
      for(int i = 0; i<TAM; i++){
        buffer[i] = rand() % 10;
        printf("%d", buffer[i]);
      }
      
      printf("\n\n");
      
      buf_cheio = 1;
      //unlock mutex
      pthread_mutex_unlock(&mutex);
    }
  }
}
//funcao consumidor
void* consumidor(void* arg){
  while(1){
    if(buf_cheio == 1){
      //lock mutex
      pthread_mutex_lock(&mutex);
      printf("CONSUMINDO!: ");
      //enchendo buffer com funcao rand
      for(int i = 0; i<TAM; i++){
        printf("%d", buffer[i]);
        buffer[i] = 0;
      }
      
      printf("\n\n");
      
      buf_cheio = 0;
      //unlock mutex
      pthread_mutex_unlock(&mutex);
    }
  }
}
*/


/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	//CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 1);
	CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 2);
        
	//CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 2);
        CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 1);
        
	CriaTarefa(tarefa_3, "Tarefa 3", PILHA_TAREFA_3, TAM_PILHA_3, 3);
	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}


/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */
//funcao produtor
void tarefa_1(void)
{
	//volatile uint16_t a = 0;
	for(;;)
	{
		//a++;
		//TarefaContinua(2);
                  SemaforoAguarda(&vazio);
                  //lock mutex
                  SemaforoAguarda(&mutex);
                  //printf("PRODUZINDO!: "); //############### NAO USAR PRINTF! ERRO DE MEMORIA!!!!! :@!!!
                  //enchendo buffer com funcao rand
                  buffer[cheio.contador] = 1;
                  //unlock mutex
                  SemaforoLibera(&mutex);
                  SemaforoLibera(&cheio);
	}
        

  
}
//funcao consumidor
void tarefa_2(void)
{
	//volatile uint16_t b = 0;
	for(;;)
	{
	//	b++;
	//	TarefaSuspende(2);	
          SemaforoAguarda(&cheio);
          //lock mutex
          SemaforoAguarda(&mutex);
          buffer[cheio.contador] = 0;
          //unlock mutex
          SemaforoLibera(&mutex);
          SemaforoLibera(&vazio);         
	}
}

void tarefa_3(void)
{
	volatile uint16_t c = 0;
	for(;;)
	{
		c++;
              //  TarefaSuspende(3);	
                TarefaEspera(100);
                
                 
                  
        }
}
