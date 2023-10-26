#define _CRT_SECURE_NO_WARNINGS // �����Ϸ� ��� �����ϱ� ���� ����
#include <stdio.h> // ���� �Է�/��� ���̺귯�� ����
#include <stdlib.h> // ���� ���̺귯�� ����

#define MAX_ELEMENT 100 /// Heap�� �ִ� ũ�� ����

typedef struct {
    int heap[MAX_ELEMENT]; // �迭�� ������ ��
    int heap_size; // ���� ���� ũ�⸦ �����ϴ� ����
} HeapType;

// �� �ʱ�ȭ �Լ�
void init(HeapType* h) {
    h->heap_size = 0; // ���� ũ�⸦ 0���� �ʱ�ȭ
}


// ���� ���� �� ��� ���� ó���ϴ� �Լ�
int is_full(HeapType* h) {
    return h->heap_size >= MAX_ELEMENT - 1; // ���� ũ�Ⱑ �ִ� ���� �������� ũ�ų� ������ �� ��ȯ
}

// ���� ��� �ִ� ��� ���� ó���ϴ� �Լ�
int is_empty(HeapType* h) {
    return h->heap_size <= 0; // ���� ũ�Ⱑ 0���� �۰ų� ������ �� ��ȯ
}

// �ִ� ���� ���Ҹ� �����ϴ� �Լ�
void insert_max_heap(HeapType* h, int item) {
    if (is_full(h)) { // is_full �Լ��� ����Ͽ� ���� �� ��� ó��
        printf("Full\n");
        return;
    }

    int i = ++(h->heap_size); // �� ũ�⸦ �����ϰ� �ε��� i�� ����

    // �θ� ���� ���Ͽ� �� �Ӽ��� ������ ������ ���Ҹ� �ùٸ� ��ġ�� �̵�
    while (i != 1 && item > h->heap[i / 2]) { 

        // �θ� ���� ���Ͽ� ��Ҹ� �ùٸ� ��ġ�� ����
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; // ��Ҹ� ���� ��ġ�� ����
}

// �ִ� ������ ��Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
int delete_max_heap(HeapType* h) {
    if (is_empty(h)) { // is_empty �Լ��� ����Ͽ� ��� �ִ� ��� ó��
        printf("Empty\n");
        return -1;
    }

    int parent, child;
    int item, temp;

    item = h->heap[1]; // �ִ� ���Ҹ� ����
    temp = h->heap[(h->heap_size)--]; // �� ũ�⸦ ���ҽ�Ű�� ������ ���Ҹ� ����
    parent = 1;
    child = 2;

    // �� �Ӽ��� �����ϸ鼭 ���Ҹ� �ùٸ� ��ġ�� �̵�
    while (child <= h->heap_size) {

        // ���� ���(child)�� �� �ڽ� ��� �� �� ū ���� ã��
        if (child < h->heap_size && h->heap[child] < h->heap[child + 1]) {
            child++;
        }

        // ���� ����� ��(temp)�� �ڽ� ��庸�� ũ�ų� ������ ���� ����
        if (temp >= h->heap[child]) {
            break;
        }

        // �θ� ��忡 �ڽ� ����� ���� �����Ͽ� �θ� ��带 �Ʒ��� �̵�
        h->heap[parent] = h->heap[child];
        parent = child; // �θ� ����� �ε����� �ڽ� ����� �ε����� ����
        child *= 2; // �ڽ� ���� �̵��Ͽ� ���� ������ �ڽ� ���� �̵�
    }

    h->heap[parent] = temp; // �ùٸ� ��ġ�� ���� ����
    return item; // ������ �ִ� ���� ��ȯ
}

int main(void) {
    HeapType heap; // HeapType ����ü ���� heap�� ����
    init(&heap); // heap�� �ʱ�ȭ�ϴ� �Լ� ȣ��

    char op; // ������ ���� op ����
    int x; // ������ ���� x ����
     
    while (1) { 
        scanf(" %c", &op); // ����ڷκ��� ���� �Է� ����

        // �Էµ� ���ڰ� 'I'�� ���
        if (op == 'I') {
            scanf("%d", &x); // ������ �Է� ����
            insert_max_heap(&heap, x); // �Էµ� ������ �ִ� ���� �����ϴ� �Լ� ȣ��
        }

        // �Էµ� ���ڰ� 'D'�� ���
        else if (op == 'D') {
            int result = delete_max_heap(&heap); // �ִ� ������ ���� �����ϴ� �Լ� ȣ��

            // ���� ������ ������ ���
            if (result != -1) {
                printf("%d\n", result); // ������ �ִ� ���Ҹ� ���
            }
        }

        // �Էµ� ���ڰ� 'Q'�� ���
        else if (op == 'Q') {
            break; // ���� ���� ����
        }
    }

    return 0;
}
