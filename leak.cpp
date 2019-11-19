#include<iostream>
#include<unistd.h>
#include<stdlib.h>

#define bucketSize 512

using namespace std;

void bktInput(int a,int b);
int main()
{
int op,pktSize;
cout<<"Enter output rate : ";
cin>>op;
for(int i=1;i<=5;i++)
{
usleep(rand()%1000);
pktSize=rand()%1000;
cout<<"\nPacket no. "<<i <<"\tPacket size ="<<pktSize;
bktInput(pktSize,op);
}
return 0;
}

void bktInput(int a,int b)
{
if(a>bucketSize)
cout<<"\n\t\tBucket overflow";
else
{
usleep(500);
while(a>b)
{
cout<<"\n\t\t"<<b<<"bytes outputed.";
a-=b;
usleep(500);
}
if(a>0)
cout<<"\n\t\tLast "<<a<<"bytes sent\t";
cout<<"\n\t\tBucket output successful";
}
}
