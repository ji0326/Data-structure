// ��� �޽��� ���� ����
#define _CRT_SECURE_NO_WARNINGS

// �ʿ��� ���̺귯�� ����
#include <stdio.h>   // ǥ�� �Է°� ��� �Լ� ���̺귯�� ����
#include <stdlib.h>  // ǥ�� ���̺귯�� �Լ� ���̺귯�� ����
#include <time.h>    // �ð� ���� �Լ� ���̺귯�� ����

// ť�� �ִ� ũ�⸦ ����
#define MAX_SIZE 10

// ���� ���� ������ ��Ÿ���� ��ũ�� ����
#define TRUE 1
#define FALSE 0

// ������ element�� ������
typedef int element;

// ť ����ü ����
typedef struct {
    element queue[MAX_SIZE];  // ��Ҹ� �����ϴ� �迭
    int front, rear;          // ť�� ���ܰ� �Ĵ��� ��Ÿ���� ����
} QueueType;

// ���� �޽��� ��� �Լ�
void error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// ť �ʱ�ȭ �Լ�
void queue_init(QueueType* q) {
    q->front = q->rear = 0;
}

// ť�� ����ִ��� ���θ� ��ȯ�ϴ� �Լ�
int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

// ť�� ���� �� �ִ��� ���θ� ��ȯ�ϴ� �Լ�
int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_SIZE == q->front);
}

// ť�� ��Ҹ� �߰��ϴ� �Լ�
void enqueue(QueueType* q, element item) {
    if (is_full(q))
        error("������");
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->queue[q->rear] = item;
}

// ť���� ��Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
element dequeue(QueueType* q) {
    if (is_empty(q))
        error("�������");
    q->front = (q->front + 1) % MAX_SIZE;
    return q->queue[q->front];
}

// �ִ� ���� ������ ����
#define MAX_VERTICES 50

// �׷��� ����ü ����
typedef struct GraphType {
    int n;                           // ������ ������ ��Ÿ���� ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // ������ ����� ��Ÿ���� 2���� �迭
} GraphType;

// ������ �湮 ���θ� �����ϴ� �迭
int visited[MAX_VERTICES];

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g) {
    int r, c;
    g->n = 0;

    // ���� ����� ��� ���Ҹ� 0���� �ʱ�ȭ
    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}

// ������ �׷����� �߰��ϴ� �Լ�
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        // ������ ������ �ʰ��� ��� ���� �޽��� ���
        fprintf(stderr, "�׷���: ������ ���� �ʰ�");
        return;
    }
    g->n++;
}

// �� ���� ���̿� ������ �����ϴ� �Լ�
void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        // ���� ��ȣ�� ��ȿ ������ ����� ���� �޽��� ���
        fprintf(stderr, "�׷���: ������ ��ȣ ����");
        return;
    }
    g->adj_mat[start][end] = 1; // start���� end�� ���� ������ ǥ��
    g->adj_mat[end][start] = 1; // end���� start�� ���� ������ ǥ��
}

// �ʺ� �켱 Ž���� ���ϴ� �Լ� (���� ��� ���)
void bfs_mat(GraphType* g, int v) {
    int w;
    QueueType q;

    queue_init(&q);
    visited[v] = TRUE;
    printf("%d �湮 ->", v + 1);
    enqueue(&q, v);

    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = 0; w < g->n; w++) {
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                printf("%d �湮 -> ", w + 1);
                enqueue(&q, w);
            }
        }
    }
}

// �迭�� �ִ� ũ�⸦ ����
#define MAX 50

// �׷��� ��� ����ü ����
typedef struct GraphNode {
    int vertex;               // ���� ��ȣ�� ����
    struct GraphNode* link;   // ���� ������ �����ϱ� ���� ������
} GraphNode;

// ���� ����Ʈ �׷��� ����ü ����
typedef struct GraphType1 {
    int n;                       // ������ ������ ����
    GraphNode* adj_list[MAX];    // �� ������ ���� ����Ʈ�� �����ϴ� �迭
} GraphType1;

// ���� ����Ʈ �׷��� �ʱ�ȭ �Լ�
void init1(GraphType1* g) {
    int v;
    g->n = 0; // �׷����� ���� ���� �ʱ�ȭ
    for (v = 0; v < MAX; v++) {
        g->adj_list[v] = NULL; // �� ������ ���� ����Ʈ �ʱ�ȭ
    }
}

// ������ ���� ����Ʈ�� �߰��ϴ� �Լ�
void insert_list_vertex(GraphType1* g, int v) {
    if (((g->n) + 1) > MAX) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�"); // ���� ���� �ʰ� �� ���� ���
        return;
    }
    g->n++; // ���� ���� ����
}

// ������ ���� ����Ʈ�� �߰��ϴ� �Լ�
void insert_list_edge(GraphType1* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����"); // ���� ��ȣ ���� �� ���� ���
        return;
    }

    node = (GraphNode*)malloc(sizeof(GraphNode)); // ���ο� ��� ����
    node->vertex = v; // ��忡 ���� ��ȣ ����
    node->link = g->adj_list[u]; // ��带 ���� ����Ʈ�� ����
    g->adj_list[u] = node; // ���� u�� ���� ����Ʈ�� ������ ���ο� ���� ����
}

// ���� ����Ʈ�� ����ϴ� �Լ�
void print_adj_list(GraphType1* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i]; // ���� ������ ���� ����Ʈ ������ ����Ű�� ������
        printf("���� %d�� ���� ����Ʈ", i + 1); // ���� ���� �̸��� ���� ����Ʈ ������ ���
        while (p != NULL) {
            printf("-> %d   ", p->vertex + 1); // ���� ���� ������ ���
            p = p->link; // ���� ���� �������� �̵�
        }
        printf("\n");
    }
}

// �湮 ���θ� �����ϴ� �迭
int visited1[MAX_VERTICES];

// �ʺ� �켱 Ž���� ���ϴ� �Լ� (���� ����Ʈ ���)
void bfs_list(GraphType1* g, int v) {
    GraphNode* w;
    QueueType q;

    queue_init(&q);
    visited1[v] = TRUE;
    printf("%d �湮 -> ", v + 1);
    enqueue(&q, v);

    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = g->adj_list[v]; w; w = w->link) {
            if (!visited1[w->vertex]) {
                visited1[w->vertex] = TRUE;
                printf("%d �湮 -> ", w->vertex + 1);
                enqueue(&q, w->vertex);
            }
        }
    }
}

// ���� ����� ����ϴ� �Լ�
void print_adj_mat(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        printf("%d   ", i + 1); // ���� ���̺� ���
        for (int j = 0; j < g->n; j++) {
            printf("%d ", g->adj_mat[i][j]); // ���� ����� ���� ���
        }
        printf("\n");
    }
}

int main(void) {
    GraphType* g;
    GraphType1* gg; // ���� ����Ʈ�� ����� �׷��� ������ ����

    g = (GraphType*)malloc(sizeof(GraphType));
    gg = (GraphType1*)malloc(sizeof(GraphType1)); // ���� ����Ʈ �׷��� ���� �Ҵ�

    graph_init(g);
    init1(gg); // ���� ����Ʈ �׷��� �ʱ�ȭ �Լ� ȣ��

    for (int i = 0; i < 8; i++) {
        insert_vertex(g, i); // ������ ���������� �߰��ϰ� ���� ��ȣ�� ���ӵ� ������ �Ҵ�
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 7);
    insert_edge(g, 7, 5);
    insert_edge(g, 7, 6);
    insert_edge(g, 5, 6);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 4);
    printf("\n");

    printf("���� ��� \n");
    print_adj_mat(g);

    printf("\n�ʺ� �켱 Ž�� (���� ���)\n");
    bfs_mat(g, 0);
    printf("\n");

    printf("\n \n");

    for (int i = 0; i < g->n; i++) {
        insert_list_vertex(gg, i); // ���� ����Ʈ �׷����� ���� �߰�
    }

    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (g->adj_mat[i][j] == 1) {
                insert_list_edge(gg, i, j); // ���� ����Ʈ �׷����� ������ ���� �߰�
            }
        }
    }

    printf("���� ����Ʈ\n\n");
    print_adj_list(gg); // ���� ����Ʈ �׷��� ���

    printf("\n\n�ʺ� �켱 Ž�� (���� ����Ʈ)\n");
    bfs_list(gg, 0);
    free(g);
    free(gg);

    return 0;
}
