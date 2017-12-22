#include<stdio.h>
#include<conio.h>
#define max 25

void main()
{
 int frame[10],used[10],index;
 int i,j,k,nf,np=0,page[max],temp;
 int flag=0,pf=0;
 
 printf("Enter no. of Frames:");
 scanf("%d",&nf);
 for(i=0;i<nf;i++)
  frame[i]=-1;
 printf("Enter pages (press -999 to exit):\n");
 for(i=0;i<max;i++)
 {
  scanf("%d",&temp);
  if(temp==-999) break;
  page[i]=temp;
  np++;
 }
 for(i=0;i<np;i++)
 {
  flag=0;
  for(j=0;j<nf;j++)
  {
   if(frame[j]==page[i])
   {
    printf("\n\t");
    flag=1;break;
   }
  }
  if(flag==0)
  {
   for(j=0;j<nf;j++) used[j]=0;
   for(j=0,temp=i-1;j<nf-1;j++,temp--)
   {
    for(k=0;k<nf;k++)
    {
     if(frame[k]==page[temp])
     used[k]=1;
    }
   }
   for(j=0;j<nf;j++)
    if(used[j]==0)
    index=j;
   frame[index]=page[i];
   printf("\nFault:  ");
   pf++;
  }
  for(k=0;k<nf;k++)
  printf("%d\t",frame[k]);
 }
 printf("\nNumber of page faults is: %d ",pf);
 getch();
}
