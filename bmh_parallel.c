#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<omp.h>

#define NUM_THREADS 4

int occ[256];

int*  lastocc(char str[])
{
int i;
char a;
for(i=0;i<128;i++)
occ[i]=-1;
int len=strlen(str);
for(i=0;i<len-1;i++)
{
a=str[i];
occ[a]=i;
}
//printf("end  of lstocc func\n");
/*printf("occurence of str chars:\n");
for(i=0;str[i]!='\0';i++)
printf("%c----%d\n",str[i],occ[(int)str[i]]);*/
return occ;
}

void bmh(char *t,int start,int end,char *p)
{
int *locc;
int i0,j,m,n;
n=end-start+1;
m=strlen(p);
//printf("length of text sent:  %d  len of pattern %d\n",n,m);
locc=lastocc(p);
i0=start;
//printf("locc[t[i0]] :  %d\n",locc[t[i0]]);
while(i0<=end-m+1)
{
  //printf("entered first while\n");
  j=m-1;
  //printf("p[%d]=%c \t t[%d]=%c\n",j,p[j],i0+j,t[i0+j]);
  while(j>=0 && p[j]==t[i0+j])
    j--;
  if(j<0)
  printf("Pattern found at %d\n",i0);
  i0+=m-1;
  //printf("i0  :  %d\n",i0);
  //printf("locc[t[i0]] :  %d\n",locc[t[i0]]);
  i0-=locc[t[i0]];
  //printf("i0  :  %d\n",i0);
}
}

int main()
{
  char pat[10];
  char *text;
  //char *text="abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqr",*pat="def";
  int n,m,i=0;
  size_t size = 0;

/* Open your_file in read-only mode */
FILE *fp = fopen("gene.txt", "r");

/* Get the buffer size */
fseek(fp, 0, SEEK_END); /* Go to end of file */
size = ftell(fp); /* How many bytes did we pass ? */

/* Set position of stream to the beginning */
rewind(fp);

/* Allocate the buffer (no need to initialize it with calloc) */
text = malloc((size + 1) * sizeof(*text)); /* size + 1 byte for the \0 */

/* Read the file into the buffer */
fread(text, size, 1, fp); /* Read 1 chunk of size bytes from fp into buffer */

/* NULL-terminate the buffer */
text[size] = '\0';

/* Print it ! */
//printf("text:  %s\n", text);
/*
//WORKS!!

FILE *fp;
fp=fopen("gene.txt","r");
fscanf(fp,"%s",text);

printf("text :  %s\n",text);
*/

/*  char ch;
          FILE *file;
          file = fopen("gene.txt","r");
          while ((ch=fgetc(file)) != EOF)
          {
            printf("ch: %c\n",ch);
            //text[i]=ch;
            //i+=1;
          }
          text[i]='\0';
          fclose(file);

*/
/*
  FILE *fp=fopen("gene.txt", "r");
  int i=0;
  while(feof(fp))
       text[i++] = fgetc(fp);
  text[i]='\0';
*/

  //scanf("%s",text);
  scanf("%s",pat);
  //printf("text : %s pattern : %s\n",text,pat);
  int lenp=strlen(pat);
  printf("Length of pattern: %d\n",lenp);
  printf("Length of pattern: %d\n",strlen(text));

  int bs=strlen(text)/NUM_THREADS;
  int rem=strlen(text)%NUM_THREADS;
  printf("bs: %d rem: %d\n",bs,rem);
  printf("num of threads %d\n",NUM_THREADS);
  int tid,start,end;

  #pragma omp parallel num_threads(NUM_THREADS) private(tid,start,end) shared(text,pat,rem,bs,m)
  {
    tid=omp_get_thread_num();
    printf("tid  %d\n",tid);
    if(tid==0)
    {
      #pragma omp critical (part1)
      {
        start=tid;
        end=bs-1;
        printf("start: %d end: %d\n",start,end);
        printf("tid= %d  text block : %d ... %d\n",tid,start,end);
        bmh(text,start,end,pat);
      }
    }
    else
    {
      #pragma omp critical (part2)
      {
        start=(tid*bs)-lenp;
        end=(tid*bs)+bs-1;
        printf("start: %d end: %d\n",start,end);
        printf("tid= %d  text block : %d ... %d\n",tid,start,end);
        bmh(text,start,end,pat);
      }
    }
 }
  if(rem!=0)
  bmh(text,(NUM_THREADS+1)*bs,strlen(text),pat);
 return 0;
}
