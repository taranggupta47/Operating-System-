#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
void *func(int n);
pthread_t philosopher[5];
pthread_mutex_t chopstick[5];
int main()
{
int i,k;
void *msg;
for(i=1;i<=5;i++)
{
k=pthread_mutex_init(&chopstick[i],NULL);
if(k==-1)
{
printf(“\n Mutex initialization failed”);
exit(1);
}
}
for(i=1;i<=5;i++)
{
k=pthread_create(&philosopher[i],NULL,(void *)func,(int *)i);
if(k!=0)
{
printf(“\n Thread creation error \n”);
exit(1);
}
}
for(i=1;i<=5;i++)
{
k=pthread_join(philosopher[i],&msg);
if(k!=0)
{
printf(“\n Thread join failed \n”);
exit(1);
}
}
for(i=1;i<=5;i++)
{
k=pthread_mutex_destroy(&chopstick[i]);
if(k!=0)
{
printf(“\n Mutex Destroyed \n”);
exit(1);
}
}
return 0;
}void *func(int n)
{
printf(“\nPhilosopher %d is thinking “,n);
pthread_mutex_lock(&chopstick[n]);//when philosopher 5 is eating he takes fork 1 and fork 5
pthread_mutex_lock(&chopstick[(n+1)%5]);
printf(“\nPhilosopher %d is eating “,n);
sleep(3);
pthread_mutex_unlock(&chopstick[n]);
pthread_mutex_unlock(&chopstick[(n+1)%5]);
printf(“\nPhilosopher %d Finished eating “,n);
}

CODE USINGS SEMAPHORES ONLY

//Dining philosopher using multiprogramming using semaphores
#include<stdio.h>
#include<fcntl.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>
sem_t *sem[20];
int n;
int main()
{
pid_t cpid[5];
char semname[5];
int i,j=0;
n = 5;
for(i=0;i<n;i++)
{
sprintf(semname,”%d”,getpid()+i);
sem[i]=sem_open(semname,O_CREAT|O_EXCL,0666,1);
if(sem[i]==SEM_FAILED)
perror(“Unable to create semaphore”);

}

for(i=0;i<n;i++)
{

cpid[i]=fork();
if(cpid[i]==0)
break;

}
if(i==n)
{
int status;
for(i=0;i<n;i++)
waitpid(cpid[i],&status,WUNTRACED);

//waitpid is a function which waits for the child process to finish executing after that //control switches back to parent
for(i=0;i<n;i++)
{
sem_close(sem[i]);
sprintf(semname,”%d”,getpid()+i);
sem_unlink(semname);
}
}
else
reader(i);

}
int reader(int val)
{
printf(“%d Thinking\n”,val+1);
while(1)
{
sem_wait(sem[val%n]);
if(!sem_trywait(sem[(val+1)%n]))
break;
else
sem_post(sem[val%n]);
}
printf(“%d Eating\n”,val+1);
sleep(2);
sem_post(sem[val%n]);
sem_post(sem[(val+1)%n]);
printf(“%d Finished Eating\n”,val+1);
}
