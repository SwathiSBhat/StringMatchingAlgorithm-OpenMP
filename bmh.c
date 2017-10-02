#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int occ[256];

int*  lastocc(char str[])
{
int i;
char a;
for(i=0;i<128;i++)
occ[i]=-1;
int len=strlen(str);
//printf("Strlen:  %d\n",len);
for(i=0;i<len-1;i++)
{
a=str[i];
//printf("str[%d]   %c (int)str[%d]=%d\n",i,str[i],i,(int)str[i]);
occ[a]=i;
//printf("occ[%c]=%d",a,occ[a]);
}
/*printf("occurence of str chars:\n");
for(i=0;str[i]!='\0';i++)
printf("%c----%d\n",str[i],occ[(int)str[i]]);
*/
return occ;
}

void bmh(char t[],char p[])
{
int *locc;
int i0,j,m,n;
n=strlen(t);
m=strlen(p);
locc=lastocc(p);
i0=0;
while(i0<=(n-m))
{
  j=m-1;
  while(j>=0 && p[j]==t[i0+j])
    j--;
  if(j<0)
  {
 // printf("i0 = %d\n",i0);
  printf("Pattern found at %d\n",i0);

  }
  //i0=i0+(m-1)-locc[t[i0+(m-1)]];
  i0+=m-1;
  i0-=locc[t[i0]];
  //printf("i0=  %d\n",i0);
}
//return -1;
}


int main()
{
  char pat[10],text[256];
  int n,m;
  /*printf("size of text: \n");
  scanf("%d",&n);
  printf("size of pattern:\n");
  scanf("%d",&m);
  printf("Enter text and pattern\n");
*/
  scanf("%s",text);
  scanf("%s",pat);
  printf("text : %s pattern : %s\n",text,pat);
  bmh(text,pat);
  /*int ans=bmh(text,pat);
  if(ans>=0)
  printf("Pattern found at index : %d\n",ans);
  else
  printf("Not found\n");
 */
 return 0;
}
