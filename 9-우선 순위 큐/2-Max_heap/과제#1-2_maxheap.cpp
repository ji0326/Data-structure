#define _CRT_SECURE_NO_WARNINGS // 컴파일러 경고를 무시하기 위한 선언
#include <stdio.h> // 포준 입력/출력 라이브러리 포함
#include <stdlib.h> // 포준 라이브러리 포함

#define MAX_ELEMENT 100 /// Heap의 최대 크기 정의

typedef struct {
    int heap[MAX_ELEMENT]; // 배열로 구현된 힙
    int heap_size; // 힙의 현재 크기를 저장하는 변수
} HeapType;

// 힙 초기화 함수
void init(HeapType* h) {
    h->heap_size = 0; // 힙의 크기를 0으로 초기화
}


// 힙이 가득 찬 경우 예외 처리하는 함수
int is_full(HeapType* h) {
    return h->heap_size >= MAX_ELEMENT - 1; // 힙의 크기가 최대 원소 개수보다 크거나 같으면 참 반환
}

// 힙이 비어 있는 경우 예외 처리하는 함수
int is_empty(HeapType* h) {
    return h->heap_size <= 0; // 힙의 크기가 0보다 작거나 같으면 참 반환
}

// 최대 힙에 원소를 삽입하는 함수
void insert_max_heap(HeapType* h, int item) {
    if (is_full(h)) { // is_full 함수를 사용하여 가득 찬 경우 처리
        printf("Full\n");
        return;
    }

    int i = ++(h->heap_size); // 힙 크기를 증가하고 인덱스 i를 설정

    // 부모 노드와 비교하여 힙 속성을 만족할 때까지 원소를 올바른 위치로 이동
    while (i != 1 && item > h->heap[i / 2]) { 

        // 부모 노드와 비교하여 요소를 올바른 위치에 삽입
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; // 요소를 최종 위치에 삽입
}

// 최대 힙에서 요소를 삭제하고 반환하는 함수
int delete_max_heap(HeapType* h) {
    if (is_empty(h)) { // is_empty 함수를 사용하여 비어 있는 경우 처리
        printf("Empty\n");
        return -1;
    }

    int parent, child;
    int item, temp;

    item = h->heap[1]; // 최대 원소를 저장
    temp = h->heap[(h->heap_size)--]; // 힙 크기를 감소시키고 마지막 원소를 저장
    parent = 1;
    child = 2;

    // 힙 속성을 유지하면서 원소를 올바른 위치로 이동
    while (child <= h->heap_size) {

        // 현재 노드(child)와 그 자식 노드 중 더 큰 값을 찾음
        if (child < h->heap_size && h->heap[child] < h->heap[child + 1]) {
            child++;
        }

        // 현재 노드의 값(temp)이 자식 노드보다 크거나 같으면 루프 종료
        if (temp >= h->heap[child]) {
            break;
        }

        // 부모 노드에 자식 노드의 값을 복사하여 부모 노드를 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child; // 부모 노드의 인덱스를 자식 노드의 인덱스로 갱신
        child *= 2; // 자식 노드로 이동하여 다음 레벨의 자식 노드로 이동
    }

    h->heap[parent] = temp; // 올바른 위치에 원소 삽입
    return item; // 삭제한 최대 원소 반환
}

int main(void) {
    HeapType heap; // HeapType 구조체 변수 heap을 선언
    init(&heap); // heap을 초기화하는 함수 호출

    char op; // 문자형 변수 op 선언
    int x; // 정수형 변수 x 선언
     
    while (1) { 
        scanf(" %c", &op); // 사용자로부터 문자 입력 받음

        // 입력된 문자가 'I'일 경우
        if (op == 'I') {
            scanf("%d", &x); // 정수를 입력 받음
            insert_max_heap(&heap, x); // 입력된 정수를 최대 힙에 삽입하는 함수 호출
        }

        // 입력된 문자가 'D'일 경우
        else if (op == 'D') {
            int result = delete_max_heap(&heap); // 최대 힙에서 원소 삭제하는 함수 호출

            // 원소 삭제가 성공한 경우
            if (result != -1) {
                printf("%d\n", result); // 삭제한 최대 원소를 출력
            }
        }

        // 입력된 문자가 'Q'일 경우
        else if (op == 'Q') {
            break; // 무한 루프 종료
        }
    }

    return 0;
}
