#include <stdio.h> // 표준 입력/출력 라이브러리를 포함
#include <stdlib.h> // 표준 라이브러리 함수를 포함
#define MAX_ELEMENT 200 // Heap의 최대 크기 정의

// 요소를 나타내는 구조체 정의
typedef struct {
	int key; // 정수형 키 값
}element;

// 최소 힙을 나타내는 구조체 정의
typedef struct {
	element heap[MAX_ELEMENT]; // 배열로 구현된 힙
	int heap_size; // 힙의 현재 크기를 저장하는 변수
}HeapType;

// 힙을 생성하는 함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType)); // 힙 구조체를 동적으로 할당하고 포인터 반환
}

// 힙을 초기화하는 함수
void init(HeapType* h) {
	h->heap_size = 0; // 힙 크기를 0으로 초기화
}

// 최소 힙에 요소를 삽입하는 함수
void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size); // 힙 크기를 증가하고 인덱스 i를 설정

	// 부모 노드와 비교하여 힙 속성을 만족할 때까지 원소를 올바른 위치로 이동
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {

		// 부모 노드와 비교하여 요소를 올바른 위치에 삽입
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // 요소를 최종 위치에 삽입
}

// 최소 힙에서 요소를 삭제하고 반환하는 함수
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1]; // 루트 노드의 요소를 삭제하고 반환
	temp = h->heap[(h->heap_size)--]; // 힙 크기를 감소하고 마지막 요소를 임시 변수에 저장
	parent = 1;
	child = 2;

	// 힙 속성을 유지하면서 원소를 올바른 위치로 이동
	while (child <= h->heap_size) {
		
		// 자식 노드 중 더 작은 자식을 찾음
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) {
			child++;
		}

		// 임시 변수의 키값과 비교하여 올바른 위치로 요소를 이동
		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp; // 요소를 최종 위치에 삽입
	return item; // 삭제된 요소를 반환
}
int main(void) {
	int numbers[] = { 10, 40, 30, 5, 12, 6, 15, 9, 60 }; // 정수 배열 선언 및 초기화
	int num[MAX_ELEMENT] = { 0, }; // 정수 배열 선언 및 초기화
	HeapType* heap; // 힙 구조체 포인터 선언

	heap = create(); // 힙을 생성하고 포인터에 할당

	init(heap); // 힙을 초기화
	element k; // 요소 구조체 변수 선언

	// 공백 트리에서 최소 힙트리가 만들어지는 과정 출력
	printf("최소 힙 트리 구성 과정:\n");
	for (int i = 0; i < 9; i++) {
		k.key = numbers[i]; // 요소의 키 값을 설정
		insert_min_heap(heap, k); // 최소 힙에 요소를 삽입
		printf("%d를 추가한 후:  ", numbers[i]);
		for (int j = 1; j <= heap->heap_size; j++) {
			printf("%d,  ", heap->heap[j].key);
		}
		printf("\n");
	}
	printf("\n==============================================================\n");

	// 최소 힙 트리 배열 내용을 출력
	printf("\n최소 힙 트리 배열 내용: ");
	while (heap->heap_size > 0) {
		element min_item = delete_min_heap(heap); // 최소 힙에서 요소를 삭제하고 반환
		printf("%d  ", min_item.key); // 삭제된 요소의 키 값을 출력
	}

	return 0;
}