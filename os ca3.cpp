#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h>  
#define MAX_CUST 10 
void *Customer(void *num); 
void *Barber(void *); 
void Wait(int secs); 
sem_t WaitingRoom; 
sem_t BarberChair; 
sem_t BarberSleep; 
sem_t SeatBelt;
int Done = 0; 
int main(int argc, char *argv[]) 
{
    pthread_t btid; 
    pthread_t tid[MAX_CUST]; 
    int i, x, Cust,Chair;
	int Num[MAX_CUST]; 
    printf("Maximum number of customers -> 10.\n");
    printf("Enter No. of Customers : ");
	scanf("%d",&Cust);
    printf("--------------------------------------------\n");
    printf("Enter No. of Chairs : ");
    scanf("%d",&Chair);
    printf("--------------------------------------------\n");
	if (Cust>MAX_CUST) { 
       printf("The maximum number of Customers is %d.\n", MAX_CUST); 
       system("PAUSE");    
       return 0;
    } 
    printf("ANSWER.\n");
	printf("---------------------------------------------\n"); 
    for (i = 0; i < MAX_CUST; i++) { 
        Num[i] = i; 
    } 
    sem_init(&WaitingRoom, 0,Chair); 
    sem_init(&BarberChair, 0, 1);
    sem_init(&BarberSleep, 0, 0); 
    sem_init(&SeatBelt, 0, 0); 
    pthread_create(&btid, NULL, Barber, NULL); 
    for (i = 0; i < Cust; i++) {
        pthread_create(&tid[i], NULL, Customer, (void *)&Num[i]); 
    } 
    for (i = 0; i < Cust; i++) { 
        pthread_join(tid[i],NULL); 
    } 
    Done = 1; 
    sem_post(&BarberSleep);  
    pthread_join(btid,NULL); 
    system("PAUSE");    
    return 0;
} 
void *Customer(void *number) { 
     int num = *(int *)number;  
     printf("Customer %d leaving for barber shop.\n", num); 
     Wait(5); 
     printf("Customer %d arrived at barber shop.\n", num); 
     sem_wait(&WaitingRoom); 
     printf("Customer %d entering waiting room.\n", num);  
     sem_wait(&BarberChair);  
     sem_post(&WaitingRoom); 
     printf("Customer %d waking the barber.\n", num); 
     sem_post(&BarberSleep);  
     sem_wait(&SeatBelt); 
     sem_post(&BarberChair); 
     printf("Customer %d leaving barber shop.\n", num); 
} 
void *Barber(void *junk) 
{ 
  while (!Done) 
  {  
    printf("Barber -> Sleeping\n"); 
    sem_wait(&BarberSleep); 
    if (!Done) 
    { 
     printf("Barber -> Cutting hair\n"); 
     Wait(3);
     printf("Barber -> Finished cutting hair.\n"); 
     sem_post(&SeatBelt); 
    } 
    else { 
         printf("Barber -> Going home.\n"); 
    } 
   }
}
void Wait(int secs) { 
     int len = 1;
     sleep(len); 
}
