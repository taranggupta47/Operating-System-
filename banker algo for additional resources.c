#include<stdio.h>
static int visited[20];
int i,j,np,nr;
int safe(int n[10][10],int ar[10],int a[10][10],int m[10][10]);
int canbeprocessed(int x[10],int y[10],int z[10],int ar[10]);
void additionalrequest(int a1[10][10],int m1[10][10],int ar1[10]);
int main()
{
 int a[10][10],m[10][10],n[10][10],ar[10],t[10];
 int a1[10][10],m1[10][10],ar1[10];
 printf("\nEnter the no of process: ");
 scanf("%d",&np); 
 printf("\nEnter the no of resources: ");
 scanf("%d",&nr);
 for(i=0;i<nr;i++)
 { 
  printf("\nTotal Amount of the Resource R%d: ",i+1);
  scanf("%d",&t[i]); 
 } 
 printf("\nEnter the allocation matrix\n\n\t");
 for(i=0;i<nr;i++)
  printf("R%d\t",i+1);
 for(i=0;i<np;i++)
 {
  printf("\nP%d\t",i+1);
  for(j=0;j<nr;j++)
  { 
   scanf("%d",&a[i][j]);
   a1[i][j]=a[i][j];
  }
 }
 printf("\n\n");
 printf("\nEnter the maximum matrix\n\n\t"); 
 for(i=0;i<nr;i++)
  printf("R%d\t",i+1);
 for(i=0;i<np;i++)
 {
  printf("\nP%d\t",i+1);
  for(j=0;j<nr;j++)
  {
   scanf("%d",&m[i][j]);
   m1[i][j]=m[i][j];
  }
 }
 for(i=0;i<np;i++)
  for(j=0;j<nr;j++)
   n[i][j]=m[i][j]-a[i][j];
     
/*Available Resource calculation*/
 for(j=0;j<nr;j++)
 {
  ar[j]=t[j];
  for(i=0;i<np;i++)
  {
   ar[j]-=a[i][j];
   ar1[j]=ar[j];
  }
 }
/*Available Resource Calculation ends*/
 if(safe(n,ar,a,m))
  printf("\n\nConclusion: System is in safe state ");
 else
  printf("\n\nConclusion: The system cannot acheive safe state" );
 additionalrequest(a1,m1,ar1);
 return 0;
}
/*Function To Check The Safe State*/
int safe(int n[][10],int ar[10],int a[][10],int m[][10])
{
 int count;
 count=0;
 printf("\nSafe State Sequence: ");
 while(count<np)
 {
  for(i=0;i<np;i++)
  {
   if((visited[i]==0) && canbeprocessed(n[i],a[i],m[i],ar))
   {
    count++;
    visited[i]=1;
    printf("P%d\t",i+1);
    break;         
   }
  }
  if(i==np)
   return 0;
 }
 return 1;
}
/*function for checking the processing of the process*/
int canbeprocessed(int x[],int y[],int z[],int ar[])
{
 for(j=0;j<nr;j++)
  if(x[j]>ar[j])
   return 0;
 for(j=0;j<nr;j++)
 {
  ar[j]+=y[j];
  y[j]=z[j]=0;
 } 
 return 1;
}
/*Additional Request*/
void additionalrequest(int a1[10][10],int m1[10][10],int ar1[10])
{
 int pno,vector[10]; 
 int n1[10][10];
 printf("\nEnter the process no which is making additional request ");
 scanf("%d",&pno);
 printf("\nEnter the request vector: ");
 for(j=0;j<nr;j++)
  scanf("%d",&vector[j]);
 for(j=0;j<nr;j++)
 {
  a1[pno][j]+=vector[j];
  ar1[j]-=vector[j];
 }
 for(i=0;i<np;i++)
  for(j=0;j<nr;j++)
   n1[i][j]=m1[i][j]-a1[i][j];
 if(safe(n1,ar1,a1,m1))
  printf("\nAllocation made \n");
 else
 {
  printf("\nAllocation cannot be made \n");
  a1[pno][j]-=vector[j];
  ar1[j]+=vector[j];
 } 
}
/*Enter the no of process: 4

Enter the no of resources: 3

Total Amount of the Resource R1: 9

Total Amount of the Resource R2: 3

Total Amount of the Resource R3: 6

Enter the allocation matrix

 R1 R2 R3 
P1 1 0 0

P2 6 1 2

P3 2 1 1

P4 0 0 2



Enter the maximum matrix

 R1 R2 R3 
P1 3 2 2

P2 6 1 3

P3 3 1 4

P4 4 2 2

Safe State Sequence: P2   P1 P3 P4 

Conclusion: System is in safe state 
Enter the process no which is making additional request 0

Enter the request vector: 1 0 1

Safe State Sequence: 

Allocation cannot be made*/
