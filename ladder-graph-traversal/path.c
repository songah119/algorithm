#include <stdio.h>
#include "backend.h"
#include "path.h"

int popped_list[N][N];
//전역변수
typedef struct Queue{
  int front, rear;
  int data[5*5757];
}Queue;

void print_path(int found, int popped[], int popped_length, int last_popped_index, int goal, int popped_list[][N]){
  int i,j,k=0;
  int result_path[100];
  int parent_index=0;
  int child_index=0;

  if(found==1){
    result_path[k++]=goal;
    result_path[k++]=last_popped_index;
    child_index=last_popped_index;
    for(i=popped_length-1;i>=0;i--){
      parent_index=popped_list[i][0];
      for(j=0;j<5757;j++){
        if(popped_list[i][j]==child_index){
          result_path[k++]=popped_list[i][0];
          child_index=parent_index;
        }
      }
    }
    int cnt=0;
    for(i=k-1;i>=0;i--){
      printf("\n%d   ",cnt);
      print_word(result_path[i]);
      cnt++;
    }
  }else{
    printf("못찾음!");
  }
}

//popped_list 배열 초기화
void popped_list_init(){
  int i,j;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      popped_list[i][j]=0;
    }
  }
  printf(".");
}

void BFS(int start, int goal){
  int found; //dest를 찾았는 지 확인하는 값
  int popped[5*5757]; // 찾은 경로의 인덱스가 저장될 배열
  int popped_length;
  int i,j,k;
  int popped_list_second;

  popped_list_init();

  //queue 초기화
  Queue q;
  q.front = 0;
  q.rear = 0;
  q.data[q.rear++] = start; //start 인덱스를 넣어줌

  //traversal
  popped_length=-1;
  while(q.front < q.rear) {
    popped[++popped_length] = q.data[q.front++]; // pop
    struct node *p = adj_list[popped[popped_length]]; //연결리스트를 참조 할 임시 노드
    popped_list[popped_length][0]=popped[popped_length];
    popped_list_second=1;
    while(p!=NULL){
      // 현재 노드의 값이 goal과 다른 경우
      if(p->index != goal){ 
        int is_in_queue=0;
        //이미 방문한 queue에 있다면 새로 push 하지 않음
        for(k=0; k<q.rear; k++){
          if(p->index==q.data[k]){
            is_in_queue=1;
          }
        }
        //queue에 없다면 push
        if(is_in_queue == 0){
          q.data[q.rear++] = p->index;
          popped_list[popped_length][popped_list_second++]=p->index;
        }
      }
      // 현재 노드의 값이 goal과 같은 경우
      else{
        found=1;
        break;
      }
      p = p->next;
      // 그 다음 노드로 이동
    }
    if(found==1)break;
  }
  print_path(found, popped, popped_length, popped[popped_length], goal, popped_list);
}

void find_path(char start[5], char goal[5]){
  int i,j,k,l;

  i=search_index(start);
  j=search_index(goal);

  if (i<0) printf("Sorry. %5s is not in the dictionary.", start);
  else if (j<0) printf("Sorry. %5s is not in the dictionary.", goal);
  else {
    print_word(i); printf(" to "); print_word(j); printf(".\n");
    BFS(i,j);
  }
}