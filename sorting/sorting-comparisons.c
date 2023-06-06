#include <stdio.h>
#define NN 25600  // data0의 연산에 필요한 buffer
int C1, C2;  // C1은 비교횟수, C2는 대입횟수

/*
Selection Sort
정렬되지 않은 값 중 최솟값을 탐색해서 앞에서부터 차례대로 최솟값을 채우면서 정렬함
*/
void selectionsort(int arr[], int size)
{
  int i, j, min, temp;
  // 마지막 숫자는 자동으로 정렬되기 때문에 (숫자 갯수-1)만큼 반복
  for (i = 0; i < size-1; i++){
    min = i; // min값의 초기화

    // i보다 한칸 뒤에서 시작해서 배열끝까지 순회하면서 최솟값을 찾는 과정
    // for문이 끝난 후에 min에는 최솟값이 설정됨
    for(j = i+1; j < size; j++){ 
      if(arr[j] < arr[least])
        min = j;
        C1++;
    } 
    C2++;
    // i번째 위치한 값에 최솟값을 채우는 과정
    temp = arr[i];
    arr[i] = arr[min];
    arr[min] = temp;
    C2++;
  }
}

/*
Insertion Sort
맨앞부터 정렬하는 알고리즘 정렬된 값의 바로 다음 값이 정렬되어야할 대상이 된다
정렬되는 대상은 대상 바로 앞의 인덱스부터 비교하면서 자신의 위치를 찾아가게 된다.
*/
void insertionsort(int arr[], int size)
{
  int i, k, j;

  for(i = 1; i < size; i++){ 
    k = arr[i]; // 배열 두번째 자리부터 key값에 대입
    j = i-1; // j는 i보다 한칸 앞의 인덱스

    // 현재 정렬된 배열은 i-1까지이므로 i-1번째 부터 역순으로 조사한다
    // j값은 음수가 아니어야 되고
    // key 값보다 정렬된 배열에 있는 값이 크면 j번째를 j+1번째로 이동
    while (j >= 0 && arr[j] > k){
      arr[j+1] = arr[j];
      j--;
      C1++;
      C2++;
    }
    arr[j+1] = k;
    C2++;
  }
}


/*
Merge Sort
배열을 하나씩이 될때까지 쪼개고 병합하는 알고리즘이다.
*/
void merge(int arr[], int l, int m, int r) // l<m<r
{
  int b[NN+1];  // buffer to store two sublists. 
  int i, j, k;

  // copy sublists to buffer
  for (i = l; i <= r; i++)
    {b[i] = arr[i];  C2++;}
  
  i = l; j = m+1; k = l; // reset indices.
  
  // merge sublists in buffer into arr[]
  while (i <= m && j <= r) {
    if (b[i] <= b[j]) 
      {arr[k++] = b[i++]; C2++;}
    else
      {arr[k++] = b[j++]; C2++;}
    C1++;
  }
  if (i > m)
    while (j <= r)
      {arr[k++] = b[j++]; C2++;}
  else
    while (i <= m)
      {arr[k++] = b[i++]; C2++;}
}

void mergesort(int arr[], int l, int r)
{
  int m;

  // 양 옆으로 쪼개면서 병합정렬을 재귀적으로 호출하는 과정
  if (l < r) {                                                                               
    m = (l+r)/2;
    mergesort(arr, l, m);
    mergesort(arr, m+1, r);
    merge(arr, l, m, r);
  }
}

/*
QuickSort
각 단계마다 pivot이 자신의 위치를 찾아가게 되고 
pivot의 양 옆을 다시 재귀적으로 호출하면서 정렬하는 알고리즘
*/

void quicksort(int arr[], int low, int high)
{
  // low(하위 인덱스)값이 high(상위 인덱스)값 이상인 경우
  // 즉 원소가 하나일 때는 그 자리가 원래 자리이므로 해당 자리가 그 원소의 자리임
  if(low >= high){
    return;
    C1++;
  }
  // pivot을 가장 왼쪽 값으로 설정
  // pivot의 바로 다음(오른쪽)값을 i로 설정
  // 가장 오른쪽값을 j로 설정
  int pivot = low;
  int i = pivot + 1;
  int j = high;
  int temp;

  // pivot의 다음값인 i와 j를 비교했을 때 해당 부등식 만족 시(값이 교차되지 않을 때)
  while(i <= j){
    while(i <= high && arr[i] <= arr[pivot]){i++; C1++;}  // low는 pivot값보다 큰값을 만날 때까지 인덱스 증가함
    while(j > low && arr[j] >= arr[pivot]){j--; C1++;}  // high는 pivot값보다 작은값을 만날 때까지 인덱스 감소함

    if(i > j){ // pivot값과 j값(=high)의 교차가 일어나는 경우
      temp = arr[j];
      arr[j] = arr[pivot];
      arr[pivot] = temp;
    }else{   // low값(=i)과 j값(=high)의 교차가 일어나는 경우
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
    C2++;
    C2++;
  }

  // pivot이 제 자리를 찾은 이후 pivot 값의 양옆을 다시 정렬함
  quicksort(arr, low, j-1);
  quicksort(arr, j+1, high);
}


int main()
{
  int i, j;
  int data0[NN];

  int N[10];
  N[1]= 100;
  N[2]= 200;
  N[3]= 300;
  N[4]= 400;
  N[5]= 500;
  N[6]= 600;
  N[7]= 700;
  N[8]= 800;
  N[9]= 900;

//배열 2개를 잡아서 바뀌기 전 배열을 카피해서 다음 함수들에게 전달해주기
//각각함수 초기화하고 


  printf("\n** Selection Sort **\n");
  for (i=1; i<10; i++) {  
    // read N[i] data
    for (j=0; j<N[i]; j++) {
      scanf("%d", &data0[j]); // read the input  
    }
    C1=C2=0;
    selectionsort(data0,N[i]); //위에서 배열 받아옴
    printf("n = %d; C1 = %d; C2 = %d.\n", N[i], C1, C2);
  }

  printf("\n** Insertion Sort **\n");
  for (i=1; i<10; i++) {  
    // read N[i] data
    for (j=0; j<N[i]; j++) {
      scanf("%d", &data0[j]); // read the input  
    }
    C1=C2=0;
    insertionsort(data0,N[i]); //위에서 배열 받아옴
    printf("n = %d; C1 = %d; C2 = %d.\n", N[i], C1, C2);
  }

  printf("\n** Merge Sort **\n");
  for (i=1; i<10; i++) {  
    // read N[i] data
    for (j=0; j<N[i]; j++) {
      scanf("%d", &data0[j]); // read the input  
    }
    C1=C2=0;
    mergesort(data0,0,N[i]-1); //위에서 배열 받아옴
    printf("n = %d; C1 = %d; C2 = %d.\n", N[i], C1, C2);
  }
  printf("\n** QuickSort **\n");
  for (i=1; i<10; i++) {  
    // read N[i] data
    for (j=0; j<N[i]; j++) {
      scanf("%d", &data0[j]); // read the input  
    }
    C1=C2=0;
    quicksort(data0,0,N[i]-1); //위에서 배열 받아옴
    printf("n = %d; C1 = %d; C2 = %d.\n", N[i], C1, C2);
  }
}
