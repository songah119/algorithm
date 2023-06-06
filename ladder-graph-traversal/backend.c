#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for delay()
#include "path.h"    

#define N 5757

// words of 5 letters
char word[N][5];

// adjacency matrix
char adj_mat[N][N];

// Function declarations
void print_word();
void init_data();
void init_adj_mat();
void init();
void print_five_chars(char *);
void print_word(int);
int search_index(char *);
void find_path(char *, char *);
void BFS(int, int);

/********* For adjacency list and queue,
we need node structure and its memory pool.
********************************************/
// record structure
struct node {
  int index;
  struct node * next;
};

#define POOL_SIZE 6*5757  // What is an appropriate size?  The average degree
// is about 5.  So this must be enough.

// pool of memory
struct node pool[POOL_SIZE];
struct node * top=pool;  // a pointer variable for stack top.

// Still use the same memory management.
void init_pool() // Initialize the pool.
{
  int i;
  struct node *r=pool;
  struct node *s;

  pool[POOL_SIZE-1].next=NULL;

  for(i=1;i<POOL_SIZE;i++) {
    s=r++;
    s->next=r;
  }
}

// When calling new_node(), make sure to check if it returns NULL.
struct node * new_node()
{
  struct node *r;

  if(top==NULL)
    return NULL;

  r=top;
  top=r->next;
  return r;
}

// Push a node to the pool.
void free_node(struct node *r)
{
  r->next=top;
  top=r;
}

/***************** End of Memory Mananagement *********************/

/***************** adjacency list *******************/
struct node * adj_list[N];

void init_adj_list()
{
  int i,j;
  struct node *p;

  for (i=0; i<N; i++)
    adj_list[i]=NULL;

  for (i=0; i<N; i++)
    for (j=N-1; j>=0; j--)    // a new node is put in front.  To make the
			      // list in ascending order, we check the
			      // vertices in reverse order.
      if (adj_mat[i][j]) {
        p=new_node();
        p->index=j;
        p->next=adj_list[i];
        adj_list[i]=p;
      }
  printf("Adjacency list was successfully constructed!\n");
}


void init_data()
{
  int i;
  FILE *f;

  if ((f=fopen("words.dat", "r")) == NULL)
    printf("Sorry, I can't open words.dat.\n");

  // skip the first four lines
  for (i=1; i<=4; i++) {
    while (getc(f)!='\n');
  }

  // start reading data
  for (i=0; i<N; i++) {
    fscanf(f, "%5c", word[i]);
    while (getc(f)!='\n');
  }

  printf("All the words were successfully read!\n");
  fclose(f);
}

int adjacent(char u[5], char v[5])
{
  int i, check=0;

  for (i=0; i<5; i++)
    if (u[i]!=v[i]) check++;

  if (check==1)
    return 1;
  else
    return 0;
}

void init_adj_mat()
{
  int i,j,l;

  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      adj_mat[i][j]=adjacent(word[i],word[j]);

  printf("Adjacency matrix was successfully constructed!\n");
}


void print_word(int k)
{
  int i;
  if(0<=k && k<N) {
    for (i=0; i<5; i++)
      putchar(word[k][i]);
  }
  else
    printf("ERROR: print_word() received a k=%d which is out of bound!\n", k);
}

/* u-v */
int compare(char u[5], char v[5])
{
  return strncmp(u, v, 5);
}

// Sequential search.
// Returns the index of the found record. (between 0 and N-1)
// Returns -1, if not found.
int search_index(char key[5])
{
  int i;

  for (i=0; i<N; i++) {
    if(compare(key,word[i])==0)
      return i;
  }
  return -1;
}

// All the initializations
void init()
{
  init_data();
  init_adj_mat();
  init_pool();
  init_adj_list();
}

int main(){
  init();
  find_path("hello","world");
  printf("\n");
  find_path("hello","axiom");
  printf("\n");
  find_path("hello","graph");
  printf("\n");
  find_path("begin","graph");
  printf("\n");
  find_path("start","begin");
  printf("\n");
  find_path("heart","paint");
  printf("\n");
}

