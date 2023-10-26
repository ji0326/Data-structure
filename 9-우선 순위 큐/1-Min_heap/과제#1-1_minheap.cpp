#include <stdio.h> // ǥ�� �Է�/��� ���̺귯���� ����
#include <stdlib.h> // ǥ�� ���̺귯�� �Լ��� ����
#define MAX_ELEMENT 200 // Heap�� �ִ� ũ�� ����

// ��Ҹ� ��Ÿ���� ����ü ����
typedef struct {
	int key; // ������ Ű ��
}element;

// �ּ� ���� ��Ÿ���� ����ü ����
typedef struct {
	element heap[MAX_ELEMENT]; // �迭�� ������ ��
	int heap_size; // ���� ���� ũ�⸦ �����ϴ� ����
}HeapType;

// ���� �����ϴ� �Լ�
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType)); // �� ����ü�� �������� �Ҵ��ϰ� ������ ��ȯ
}

// ���� �ʱ�ȭ�ϴ� �Լ�
void init(HeapType* h) {
	h->heap_size = 0; // �� ũ�⸦ 0���� �ʱ�ȭ
}

// �ּ� ���� ��Ҹ� �����ϴ� �Լ�
void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size); // �� ũ�⸦ �����ϰ� �ε��� i�� ����

	// �θ� ���� ���Ͽ� �� �Ӽ��� ������ ������ ���Ҹ� �ùٸ� ��ġ�� �̵�
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {

		// �θ� ���� ���Ͽ� ��Ҹ� �ùٸ� ��ġ�� ����
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // ��Ҹ� ���� ��ġ�� ����
}

// �ּ� ������ ��Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1]; // ��Ʈ ����� ��Ҹ� �����ϰ� ��ȯ
	temp = h->heap[(h->heap_size)--]; // �� ũ�⸦ �����ϰ� ������ ��Ҹ� �ӽ� ������ ����
	parent = 1;
	child = 2;

	// �� �Ӽ��� �����ϸ鼭 ���Ҹ� �ùٸ� ��ġ�� �̵�
	while (child <= h->heap_size) {
		
		// �ڽ� ��� �� �� ���� �ڽ��� ã��
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) {
			child++;
		}

		// �ӽ� ������ Ű���� ���Ͽ� �ùٸ� ��ġ�� ��Ҹ� �̵�
		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp; // ��Ҹ� ���� ��ġ�� ����
	return item; // ������ ��Ҹ� ��ȯ
}
int main(void) {
	int numbers[] = { 10, 40, 30, 5, 12, 6, 15, 9, 60 }; // ���� �迭 ���� �� �ʱ�ȭ
	int num[MAX_ELEMENT] = { 0, }; // ���� �迭 ���� �� �ʱ�ȭ
	HeapType* heap; // �� ����ü ������ ����

	heap = create(); // ���� �����ϰ� �����Ϳ� �Ҵ�

	init(heap); // ���� �ʱ�ȭ
	element k; // ��� ����ü ���� ����

	// ���� Ʈ������ �ּ� ��Ʈ���� ��������� ���� ���
	printf("�ּ� �� Ʈ�� ���� ����:\n");
	for (int i = 0; i < 9; i++) {
		k.key = numbers[i]; // ����� Ű ���� ����
		insert_min_heap(heap, k); // �ּ� ���� ��Ҹ� ����
		printf("%d�� �߰��� ��:  ", numbers[i]);
		for (int j = 1; j <= heap->heap_size; j++) {
			printf("%d,  ", heap->heap[j].key);
		}
		printf("\n");
	}
	printf("\n==============================================================\n");

	// �ּ� �� Ʈ�� �迭 ������ ���
	printf("\n�ּ� �� Ʈ�� �迭 ����: ");
	while (heap->heap_size > 0) {
		element min_item = delete_min_heap(heap); // �ּ� ������ ��Ҹ� �����ϰ� ��ȯ
		printf("%d  ", min_item.key); // ������ ����� Ű ���� ���
	}

	return 0;
}