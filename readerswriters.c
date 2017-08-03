#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

/*#define READERS    20      
#define WRITERS    3*/        



pthread_mutex_t db;
pthread_mutex_t mutex;
int rc;
int lr, lw;

void read_db(int lr){
  /*quanto tempo o leitor permanecerá lendo a base de dados*/
  printf("Total de %d leitores lendo agora.\n",rc);
  sleep(lr);
}
  
void use_db(){
  /*quanto tempo o leitor permanecerá utilizando os dados lidos*/
  int use;
  use = rand() % 20;
  printf("Usuário utilizando conhecimento\n");
  sleep(use);
}

void think_db(){
  /*quanto tempo o escritor gasta pensando no que irá escrever*/
  int think;
  think = rand() % 10;
  printf("Escritor pensando no que irá escrever\n");
  sleep(think);
}

void write_db(int lw){
  /*quanto tempo o escritor gasta escrevendo na base de dados*/
  printf("Escritor escrevendo no banco de dados\n");
  sleep(lw); 
}

void reader() {
  while (1) { 
    pthread_mutex_lock(&mutex);   
    rc++;                              

    if(rc == 1) 
       pthread_mutex_lock(&db);
    
    pthread_mutex_unlock(&mutex);

    read_db(lr);
    
    pthread_mutex_lock(&mutex);
    rc--;

    if(rc == 0) 
      pthread_mutex_unlock(&db);
      
    pthread_mutex_unlock(&mutex);
    use_db();
  }
}

void writer() {
    while(1){
        think_db();
        pthread_mutex_lock(&db);
        write_db(lw);
        pthread_mutex_unlock(&db);
    }
}


int main(){
  int READERS = 0, WRITERS = 0;
  
  printf("Quantidade de leitores: ");
  scanf("%d",&READERS);
  printf("Quantidade de escritores: ");
  scanf("%d",&WRITERS);

  printf("Tempo de leitura: ");
  scanf("%d",&lr);
  printf("Tempo de escrita: ");
  scanf("%d",&lw);

  pthread_t writerthreads[WRITERS], readerthreads[READERS]; 
  int i;

  pthread_mutex_init(&db, NULL);
  pthread_mutex_init(&mutex, NULL);


   /*n threads writer*/
  for(i=0;i < WRITERS;i++)
        pthread_create( &writerthreads[i], NULL,(void *) writer, NULL);

  /*n threads reader*/
  for(i=0;i < READERS;i++)
        pthread_create( &readerthreads[i], NULL,(void *) reader, NULL);

  for(i=0;i < WRITERS;i++)
        pthread_join(writerthreads[i], NULL);

  for(i=0;i < READERS;i++)
        pthread_join(readerthreads[i], NULL);


  return 0;
}