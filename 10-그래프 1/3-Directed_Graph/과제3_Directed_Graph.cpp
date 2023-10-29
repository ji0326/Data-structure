#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VERTICES 50 // �ִ� ���� ���� ����
#define MAX 50 // �迭�� �ִ� ũ�⸦ ����

#define TRUE 1 // ���� ��Ÿ���� ��� ����
#define FALSE 0 // ������ ��Ÿ���� ��� ����


// �׷����� �� ������ ��Ÿ���� ����ü
typedef struct GraphNode {
    int vertex;  // ���� ��ȣ�� ����
    struct GraphNode* link;  // ���� ������ �����ϱ� ���� ������
} GraphNode;

// ���� ����� ����� �׷��� ����ü
typedef struct GraphType {
    int n;  // ������ ������ ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // ���� �� ���� ���θ� �����ϴ� ���� ���
} GraphType;

// �׷��� �ʱ�ȭ �Լ�
void init(GraphType* g) {
    int r, c;
    g->n = 0;  // ������ ���� �ʱ�ȭ
    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0; // ���� ��� �ʱ�ȭ
        }
    }
}

// ������ �׷����� �߰��ϴ� �Լ�
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�"); // ���� ���� �ʰ� �� ���� ���
        return;
    }
    g->n++;
}

// ������ �׷����� �߰��ϴ� �Լ�
void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "�׷���: ������ ��ȣ ����");  // ���� ��ȣ ���� �� ���� ���
        return;
    }
    g->adj_mat[start][end] = 1; // ���� ��Ŀ��� �ش� ������ Ȱ��ȭ
   // g->adj_mat[end][start] = 1;
}


// ���� ����� ����ϴ� �Լ�
void print_adj_mat(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        printf("%c\t", 'A' + i);  // ���� �̸��� ���
        for (int j = 0; j < g->n; j++) {
            printf("%2d ", g->adj_mat[i][j]);  // ���� ����� ���� ���
        }
        printf("\n");
    }
}

int visited[MAX_VERTICES];  // �湮 ���θ� �����ϴ� �迭

// ���� ����� ����� ���� �켱 Ž��(DFS) �Լ�
void dfs_mat(GraphType* g, int v) {
    int w;
    visited[v] = TRUE;  // ������ �湮�� ������ ǥ��
    printf("%c  ", 'A' + v);  // �湮�� ������ ���
    for (w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w]) {
            dfs_mat(g, w);  // �湮���� ���� ���� ������ ��������� Ž��
        }
    }
}


// ���� ����Ʈ�� ����� �׷��� ����ü
typedef struct GraphType1 {
    int n;  // ������ ������ ����
    GraphNode* adj_list[MAX];  // �� ������ ���� ����Ʈ�� �����ϴ� �迭
} GraphType1;


// �׷��� �ʱ�ȭ �Լ�
void init1(GraphType1* g) {
    int v;
    g->n = 0;  // ������ ���� �ʱ�ȭ
    for (v = 0; v < MAX; v++) {
        g->adj_list[v] = NULL;  // ���� ����Ʈ �ʱ�ȭ

    }

}

// ������ ���� ����Ʈ�� �߰��ϴ� �Լ�
void insert_list_vertex(GraphType1* g, int v) {
    if (((g->n) + 1) > MAX) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�"); // ���� ���� �ʰ� �� ���� ���
        return;
    }

    g->n++;
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
    g->adj_list[u] = node;
}

// ���� ����Ʈ�� ����ϴ� �Լ�
void print_adj_list(GraphType1* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* p = g->adj_list[i];
        printf("���� %c�� ���� ����Ʈ", 'A' + i);  // ���� �̸��� ���� ����Ʈ ������ ���
        while (p != NULL) {
            printf("-> %c", 'A' + p->vertex);  // ���� ������ ���
            p = p->link; // ���� ���� �������� �̵�
        }
        printf("\n");
    }
}


int visited1[MAX_VERTICES];  // �湮 ���θ� �����ϴ� �迭

// ���� ����Ʈ�� ����� ���� �켱 Ž��(DFS) �Լ�
void dfs_list(GraphType1* g, int v) {
    GraphNode* w;
    visited1[v] = TRUE;  // ������ �湮�� ������ ǥ��
    printf("���� %c -> ", 'A' + v); // �湮�� ������ ���
    for (w = g->adj_list[v]; w;w = w->link) { 
        if (!visited1[w->vertex])
            dfs_list(g, w->vertex);  // �湮���� ���� ���� ������ ��������� Ž��
    }
}


int main(void) {

    GraphType* g; // ���� ����� ����ϴ� �׷���
    GraphType1* gg; // ���� ����Ʈ�� ����ϴ� �׷���
    g = (GraphType*)malloc(sizeof(GraphType)); // ���� ��� �׷��� �޸� �Ҵ�
    gg = (GraphType1*)malloc(sizeof(GraphType1)); // ���� ����Ʈ �׷��� �޸� �Ҵ�
    init(g); // �׷��� �ʱ�ȭ
    init1(gg); // �׷��� �ʱ�ȭ

    // 7���� ������ �׷����� �߰�
    for (int i = 0; i < 7; i++) {
        insert_vertex(g, i);
    }

    // ���� ������ �߰��Ͽ� �׷��� ����
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 0, 5);
    insert_edge(g, 0, 6);

    insert_edge(g, 1, 0);
    insert_edge(g, 1, 6);

    insert_edge(g, 2, 0);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 2);
    insert_edge(g, 2, 4);
    insert_edge(g, 2, 5);
    insert_edge(g, 2, 6);

    insert_edge(g, 3, 2);
    insert_edge(g, 3, 4);

    insert_edge(g, 4, 2);
    insert_edge(g, 4, 3);
    insert_edge(g, 4, 4);
    insert_edge(g, 4, 5);

    insert_edge(g, 5, 2);
    insert_edge(g, 5, 5);
    insert_edge(g, 5, 6);

    insert_edge(g, 6, 1);
    insert_edge(g, 6, 2);
    insert_edge(g, 6, 3);
    insert_edge(g, 6, 4);
    insert_edge(g, 6, 5);
    printf("\n");



    print_adj_mat(g); // ���� ��� ���

    printf("���� ��� DFS: ");

    // �湮 �迭 �ʱ�ȭ �� DFS ����
    for (int i = 0; i < 7; i++) {
        visited[i] = FALSE; // visited1 �迭 �ʱ�ȭ
    }


    for (int i = 0; i < 7; i++) {
        if (!visited[i]) {
            dfs_mat(g, i);
        }
    }

    printf("\n \n");

    // 7���� ������ �׷����� �߰�
    for (int i = 0; i < g->n; i++) {
        insert_list_vertex(gg, i);
    }

    // ���� ����� ������� ���� ����Ʈ ���� �߰�
    for (int i = 0; i < g->n;i++) {
        for (int j = 0; j < g->n; j++) {
            if (g->adj_mat[i][j] == 1) {
                insert_list_edge(gg, i, j);
            }
        }
    }

    print_adj_list(gg);  // ���� ����Ʈ ���


    printf("���� ����Ʈ DFS: ");
    // �湮 �迭 �ʱ�ȭ �� DFS ����
    for (int i = 0; i < 7; i++) {
        visited1[i] = FALSE; // visited2 �迭 �ʱ�ȭ
    }

    for (int i = 0; i < 7; i++) {
        if (!visited1[i]) {
            dfs_list(gg, i);
        }
    }
    free(g); // �׷��� �޸� ����
    free(gg); // �׷��� �޸� ����
    return 0;
}
