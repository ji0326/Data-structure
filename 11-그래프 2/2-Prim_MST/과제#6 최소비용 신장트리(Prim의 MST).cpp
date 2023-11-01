#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;                    // �׷����� ���� ���� ��Ÿ���� ����
	int weight[MAX_VERTICES][MAX_VERTICES];  // ���� ����ġ�� �����ϴ� 2���� �迭
} GraphType;

int selected[MAX_VERTICES];  // ���õ� ������ ��Ÿ���� �迭
int distance[MAX_VERTICES];  // ���� �������� �� ���������� �ִ� �Ÿ��� �����ϴ� �迭

int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selected[i]) {  // ���� ���õ��� ���� ���� �߿���
			v = i;           // ù ��°�� �߰ߵ� ������ ����
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && (distance[i] < distance[v]))  // ���õ��� ���� ���� �߿��� �ּ� �Ÿ��� ������ ������ ã��
			v = i;
	}
	return (v);  // �ּ� �Ÿ��� ������ ������ �ε��� ��ȯ
}

void print_selected_distance(int n) {
	int i;
	printf("selected[]: ");
	for (i = 0; i < n; i++) {
		printf("%d ", selected[i]);  // ���õ� ���� ���
	}
	printf("\n");

	printf("distance[]: ");
	for (i = 0; i < n; i++) {
		printf("%d ", distance[i]);  // ���� �������κ����� �ִ� �Ÿ� ���
	}
	printf("\n\n");
}

void prim(GraphType* g, int s) {
	int i, u, v;
	int total_weight = 0;  // MST�� ���� ����ġ�� ���� �����ϱ� ���� ����
	for (u = 0; u < g->n; u++) {
		distance[u] = INF;  // ��� ������ �Ÿ��� ���Ѵ�� �ʱ�ȭ
	}
	distance[s] = 0;  // ���� ������ �Ÿ��� 0���� �ʱ�ȭ
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);  // �ּ� �Ÿ��� ������ ������ ����
		selected[u] = TRUE;  // �ش� ������ �������� ǥ��
		if (distance[u] == INF) return;  // ���õ� ������ ������ ����
		printf("���� %d �߰�\n", u);  // ���� ������ ������ ���
		print_selected_distance(g->n);  // ���õ� ������ �Ÿ� ���� ���

		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {  // ���� ������ ����� ���� �߿���
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];  // �ִ� �Ÿ� ����
				}
			}
		}
	}

	// MST�� ���� ����ġ�� �� ���
	for (u = 0; u < g->n; u++) {
		if (distance[u] != INF) {
			total_weight += distance[u];  // ���õ� ������ ����ġ�� ����
		}
	}

	printf("MST ������ ����ġ ��: %d\n", total_weight);  // MST�� ���� ����ġ�� �� ���
}

int main(void) {

	// �׷��� �ʱ�ȭ
	GraphType g = { 9,
	{{ 0, 35, INF, INF, 245, INF, INF, INF, INF },
	{ 35, 0, 123, INF, INF, 154, INF, INF, INF },
	{ INF, 123, 0, 117, INF, 165, INF, 222, INF },
	{ INF, INF, 117, 0, INF, INF, INF, INF, INF },
	{ 245, INF, INF, INF, 0, 87, 98, INF, INF },
	{ INF, 154, 165, INF, 87, 0, 122, 155, INF },
	{ INF, INF, INF, INF, 98, 122, 0, INF, INF },
	{ INF, INF, 222, INF, INF, 155, INF, 0, 164 },
	{ INF, INF, INF, INF, INF, INF, INF, 164, 0 }}
	};

	prim(&g, 1);  // prim �˰����� ����Ͽ� MST ����
	return 0;
}
