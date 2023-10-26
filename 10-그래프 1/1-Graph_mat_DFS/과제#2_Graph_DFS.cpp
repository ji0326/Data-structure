#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VERTICES 50 // �ִ� ���� ������ 50���� ����

#define TRUE 1 // ������ ���� ��Ÿ��
#define FALSE 0 // ������ ������ ��Ÿ��

// �׷��� ����ü ����
typedef struct GraphType {
	int n; // ������ ������ ��Ÿ���� ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // ������ ����� ��Ÿ���� 2���� �迭
}GraphType;

// �׷��� �ʱ�ȭ �Լ� ����
void init(GraphType* g) {
	int r, c;
	g->n = 0;

	// ���� ����� ��� ���Ҹ� 0���� �ʱ�ȭ
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

// ������ �����ϴ� �Լ� ����
void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {

		// ������ ������ �ʴ� ������ �ʰ��� ��� ���� �޽��� ���
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

// ���� ����� ����ϴ� �Լ�
void print_adj_mat(GraphType* g)
{
	for (int i = 0; i < g->n; i++) {
		printf("%c\t", 'A' + i); // ���� ���̺� ���
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]); // ���� ����� ���� ���
		}
		printf("\n");
	}
}


// ���� �켱 Ž��(DFS)�� �����ϴ� �Լ�
int visited[MAX_VERTICES]; // �湮 ���θ� ��Ÿ���� �迭

void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = TRUE; // ���� ������ �ݹ��� ������ ǥ��
	printf("%c  ", 'A' + v); // ���� ������ ���
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			// ���� ������ ����� ���� �� �湮���� ���� ������ �ִٸ� ��������� Ž��
			dfs_mat(g, w);
}

// �� ������ �Է����� �޾� ������ 0, �ٸ��� 1�� ��ȯ�ϴ� �Լ�
int random_same(int x, int y) {
	if (x == y) {
		return 0;
	}
	return 1;
}

// �׷��� g�� ������ �߰��ϴ� �Լ� ����
void adj_produce(GraphType* g,int num1, int line) {
	srand(time(NULL)); // ���� ������ ���� ���� �ð��� �õ�� ���

	// ������ �� ������ ������ �迭 �Ҵ�
	int* line_list_x = (int*)malloc(sizeof(int) * line);
	int* line_list_y = (int*)malloc(sizeof(int) * line);

	//�迭 �ε���
	int index = 0;

	// line ���� ��ŭ �ݺ��Ͽ� ������ ������ ����
	for (int i = 0; i < line; i++) {

		// �������� ���� ����
		int randomx = rand() % num1;
		int randomy = rand() % num1;
		int chk = 0;

		// ���� ������ �ߺ��ؼ� �������� �ʵ��� ����
		if (random_same(randomx, randomy)) {

			// �̹� ������ ������ ���Ͽ� �ߺ� Ȯ��
			for (int j = 0; j < index; j = j++) {
				if ((randomx == line_list_x[j] && randomy == line_list_y[j]) || (randomx == line_list_y[j] && randomy == line_list_x[j]) || (randomx == randomy)) {
					chk = 1;
					i--; // �ߺ��� ��� �ٽ� �õ�
					break;
				}
			}
			// chk ������ 1�� �ƴ� ��� (�ߺ��� ������ ���� ���)
			if (chk != 1) {

				// �� ������ ������������ �����Ͽ� �ߺ��� ���ϱ� ���� �۾�
				if (randomx < randomy) {
					line_list_x[index] = randomx;
					line_list_y[index] = randomy;
				}
				else {
					line_list_x[index] = randomy;
					line_list_y[index] = randomx;
				}
				index++; // �ߺ��� ���� ������ �迭�� �����ϰ� �迭 �ε��� ����
				insert_edge(g, randomx, randomy); // �ߺ��� ���� ������ �׷����� �߰�
			}
		}
		else {
			i--; // ���� ������ �����Ϸ��� �� ��� �ٽ� �õ�
		}
	}
}


int main(void) {
	int num1 = 0, line = 0;
	int randomx, randomy;


	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));

	init(g);

	printf("������ ������?");
	scanf("%d", &num1);

	for (int i = 0; i < num1; i++) {
		insert_vertex(g, i); // �Է¹��� ������ ������ŭ �׷����� ���� �߰�
	}
	printf("���� ���� �׷��� ����\n");

	printf("���� ��:");
	scanf("%d", &line);

	adj_produce(g, num1, line); // ���� ������ �����Ͽ� �׷����� �߰��ϴ� �Լ� ȣ��
	print_adj_mat(g);  // �׷����� ���� ����� ����ϴ� �Լ� ȣ��

	printf("DFS: ");
	for (int i = 0; i < num1;i++) {
		if (!visited[i]) {
			dfs_mat(g, i); // �湮���� ���� �������� ���� �켱 Ž���� �����ϴ� �Լ� ȣ��
		}
	}

	free(g);
	
}