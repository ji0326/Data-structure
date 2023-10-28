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
    int vertex; // ���� ��ȣ�� ����
    struct GraphNode* link; // ���� ������ �����ϱ� ���� ������
} GraphNode;

// ���� ����� ����� �׷��� ����ü
typedef struct GraphType {
    int n; // ������ ������ ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // ���� �� ���� ���θ� �����ϴ� ���� ���
} GraphType;

// �׷��� �ʱ�ȭ �Լ�
void init(GraphType* g) {
    int r, c;
    g->n = 0; // ������ ���� �ʱ�ȭ
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
        fprintf(stderr, "�׷���: ������ ��ȣ ����"); // ���� ��ȣ ���� �� ���� ���
        return;
    }
    g->adj_mat[start][end] = 1; // ���� ��Ŀ��� �ش� ������ Ȱ��ȭ
    g->adj_mat[end][start] = 1; // ������ �׷����̹Ƿ� ��������� ����
}



// ���� ����� ����ϴ� �Լ�
void print_adj_mat(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        printf("%c\t", 'A' + i); // ���� �̸��� ���
        for (int j = 0; j < g->n; j++) {
            printf("%2d ", g->adj_mat[i][j]); // ���� ����� ���� ���
        }
        printf("\n");
    }
}



// �湮 ���θ� �����ϴ� �迭
int visited[MAX_VERTICES];

// ���� ����� ����� ���� �켱 Ž��(DFS) �Լ�
void dfs_mat(GraphType* g, int v) {
    int w;
    visited[v] = TRUE; // ������ �湮�� ������ ǥ��
    printf("%c  ", 'A' + v); // �湮�� ������ ���
    for (w = 0; w < g->n; w++) {
        if (g->adj_mat[v][w] && !visited[w]) {
            dfs_mat(g, w); // �湮���� ���� ���� ������ ��������� Ž��
        }
    }
}

// �׷����� ���� ����Ʈ�� ǥ���ϱ� ���� ����ü
typedef struct GraphType1 {
    int n; // ������ ������ ����
    GraphNode* adj_list[MAX]; // �� ������ ���� ����Ʈ�� �����ϴ� �迭
} GraphType1;

// �׷��� �ʱ�ȭ �Լ�
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
        printf("���� %c�� ���� ����Ʈ", 'A' + i); // ���� ���� �̸��� ���� ����Ʈ ������ ���
        while (p != NULL) {
            printf("-> %c", 'A' + p->vertex); // ���� ���� ������ ���
            p = p->link; // ���� ���� �������� �̵�
        }
        printf("\n");
    }
}



// �湮 ���θ� �����ϴ� �迭
int visited1[MAX_VERTICES];

// ���� ����Ʈ�� ����� ���� �켱 Ž��(DFS) �Լ�
void dfs_list(GraphType1* g, int v) {
    GraphNode* w;
    visited1[v] = TRUE; // ������ �湮�� ������ ǥ��
    printf("���� %c -> ", 'A' + v); // �湮�� ������ ���
    for (w = g->adj_list[v]; w; w = w->link) {
        if (!visited1[w->vertex])
            dfs_list(g, w->vertex); // �湮���� ���� ���� ������ ��������� Ž��
    }
}

// �� ���� x�� y�� �������� Ȯ���ϴ� �Լ�
int random_same(int x, int y) {
    if (x == y) {
        return 0; // x�� y�� ������ 0�� ��ȯ
    }
    return 1; // x�� y�� �ٸ��� 1�� ��ȯ
}

// �׷����� ������ ������ �߰��ϴ� �Լ�
void adj_produce(GraphType* g, int num1, int line) {
    srand(time(NULL)); // ���� �߻��� ���� �õ� ����

    int* line_list_x = (int*)malloc(sizeof(int) * line); // ������ ������ ���� ������ �����ϴ� �迭
    int* line_list_y = (int*)malloc(sizeof(int) * line); // ������ ������ �� ������ �����ϴ� �迭

    int index = 0; // �迭 �ε��� ���� �ʱ�ȭ

    for (int i = 0; i < line; i++) { // �־��� ���� ������ŭ �ݺ�
        int randomx = rand() % num1; // 0���� (num1-1) ������ ���� ���� (���� ����)
        int randomy = rand() % num1; // 0���� (num1-1) ������ ���� ���� (�� ����)
        int chk = 0; // ���� �ߺ� Ȯ���� ���� ���� �ʱ�ȭ

        if (random_same(randomx, randomy)) { // ���� ������ �� ������ �ٸ� ���
            for (int j = 0; j < index; j++) { // �̹� ������ ������ ��
                if ((randomx == line_list_x[j] && randomy == line_list_y[j]) ||
                    (randomx == line_list_y[j] && randomy == line_list_x[j]) || (randomx == randomy)) {
                    chk = 1; // �ߺ��� ������ ������ chk�� 1�� ����
                    i--; // �ߺ��� ��� ���� �ݺ��� �ٽ� �����ϵ��� ����
                    break; // �ݺ� ����
                }
            }
            if (chk != 1) { // �ߺ��� ������ ���� ���
                if (randomx < randomy) {
                    line_list_x[index] = randomx; // ���� ������ ���� �������� ����
                    line_list_y[index] = randomy; // ū ������ �� �������� ����
                }
                else {
                    line_list_x[index] = randomy; // ū ������ ���� �������� ����
                    line_list_y[index] = randomx; // ���� ������ �� �������� ����
                }
                index++; // �迭 �ε��� ����
                insert_edge(g, randomx, randomy); // �׷����� ���� �߰�
            }
        }
        else {
            i--; // ���� ������ �� ������ ���� ��� ���� �ݺ��� �ٽ� �����ϵ��� ����
        }
    }

    free(line_list_x); // �������� �Ҵ��� �迭 �޸� ����
    free(line_list_y); // �������� �Ҵ��� �迭 �޸� ����
}


int main(void) {
    int num1 = 0, line = 0;

    GraphType* g; // ���� ����� ����� �׷��� ������ ����
    GraphType1* gg; // ���� ����Ʈ�� ����� �׷��� ������ ����
    g = (GraphType*)malloc(sizeof(GraphType)); // ���� ��� �׷��� ���� �Ҵ�
    gg = (GraphType1*)malloc(sizeof(GraphType1)); // ���� ����Ʈ �׷��� ���� �Ҵ�
    init(g); // ���� ��� �׷��� �ʱ�ȭ �Լ� ȣ��
    init1(gg); // ���� ����Ʈ �׷��� �ʱ�ȭ �Լ� ȣ��
    printf("������ ������?");
    scanf("%d", &num1); // ����ڷκ��� ������ ���� �Է� ����

    for (int i = 0; i < num1; i++) {
        insert_vertex(g, i); // ���� ��� �׷����� ���� �߰�
    }
    printf("���� ���� �׷��� ����\n");

    printf("���� ��:");
    scanf("%d", &line); // ����ڷκ��� ������ ���� �Է� ����

    adj_produce(g, num1, line); // ���� ��� �׷����� ������ ���� �߰�
    print_adj_mat(g); // ���� ��� �׷��� ���

    printf("���� ��� DFS: ");
    for (int i = 0; i < num1; i++) {
        if (!visited[i]) {
            dfs_mat(g, i); // ���� ��� �׷����� ���� DFS ����
        }
    }

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

    print_adj_list(gg); // ���� ����Ʈ �׷��� ���

    printf("���� ����Ʈ DFS: ");
    for (int i = 0; i < num1; i++) {
        if (!visited1[i]) {
            dfs_list(gg, i); // ���� ����Ʈ �׷����� ���� DFS ����
        }
    }
    free(g); // ���� �Ҵ�� ���� ��� �׷��� �޸� ����
    free(gg); // ���� �Ҵ�� ���� ����Ʈ �׷��� �޸� ����
    return 0;
}