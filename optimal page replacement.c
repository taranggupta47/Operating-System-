#include<stdio.h>
#include<conio.h>
#define max 25

void main()
{
 int frame[10],length[10],index,highest;
 int i,j,k,nf,np=0,page[max],temp;
 int flag=0,pf=0,found=0;
 
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
   for(j=0;j<nf;j++)
   {
    for(temp=i+1;temp<np;temp++)
    {
     length[j]=0;
     if (frame[j]==page[temp])
     {length[j]=temp-i;break;}
    }
   }
   found=0;
   for(j=0;j<nf;j++)
   {
    if(length[j]==0)
    {
     index=j;
     found=1;
     break;
    }
   }
   if(found==0)
   {
    highest=length[0];
    index=0;
    for(j=1;j<nf;j++)
    {
     if(highest<length[j])
     {
      highest=length[j];
      index=j;
     }
    }
   }
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
