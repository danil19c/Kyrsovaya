//�������� ������
//�������� ������� ������ 21��3: ����� �.�.
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<windows.h>
#include<string.h>
#include<conio.h>
#include <fstream>
#include<queue>


using namespace std;
queue <int> Q;
vector <int> comp;

int** G = NULL;
int* numV = NULL;

void findComponents(int num, FILE* f); //���������� �������

//��������� ��������� �������
void generateMatrix(int num) {
	if (num == 0) return;
	for (int i = 0; i < num; i++) {
		numV[i] = 1;
		for (int j = 0; j < num; j++) {
			if (i == j) {
				G[i][j] = 0;
				continue;
			}
			G[i][j] = rand() % 2;
		}
	}
}
//����������� ������� ������� � ��������� ��� ��� ������
void numberVershin(int* num) {
	if (*num != 0 && G != NULL) {
		for (int i = 0; i < *num; i++) {
			free(G[i]);
		}
		free(G);
		free(numV);
	}
	system("cls");
	printf("������ �����: ");
	scanf_s("%d", &*num);
	G = (int**)malloc(*num * sizeof(int*));
	numV = (int*)malloc(*num * sizeof(int));
	for (int i = 0; i < *num; i++) {
		G[i] = (int*)malloc(*num * sizeof(int));
		numV[i] = NULL;
	}
}
//����� ������� �� �����
void printMatrix(int num, int v) {
	if (num == 0 || numV[v] == NULL) return;

	FILE* f = fopen("answer.txt", "w");
	system("cls");

	printf("������� ��������� \n");
	fprintf(f, "������� ��������� \n");
	printf("\n   ");
	fprintf(f, "\n   ");
	for (int i = 0; i < num; i++) {
		printf("  %c", (i + 97));
		fprintf(f, "  %c", (i + 97));
	}
	printf("\n    ");
	fprintf(f, "\n    ");
	for (int i = 0; i < num * 3; i++) {
		printf("_");
		fprintf(f, "_");
	}
	printf("\n");
	fprintf(f, "\n");
	for (int i = 0; i < num; i++) {
		printf(" %c | ", (i + 97));
		fprintf(f, " %c | ", (i + 97));
		for (int j = 0; j < num; j++) {
			printf("%d  ", G[i][j]);
			fprintf(f, "%d  ", G[i][j]);
		}
		printf("\n");
		fprintf(f, "\n");
	}
	fprintf(f, "\n");

	findComponents(num, f);

	fclose(f);
	printf("\n\n��� ����������� ������� ����� ������...");
	_getch();
}
//���������� ����� �������� � �������
void scanfMatrix(int num) {
	if (num == 0 || G == NULL) return;
	int x = 0, y = 0;
	for (int i = 0; i < num; i++) {
		numV[i] = 1;
		for (int j = 0; j < num; j++) {
			G[i][j] = 0;
		}
	}
	while (true) {
		system("cls");
		printf("�� ������� ������� � ������� � ��� �������\n");
		printf("��������� ������ ���������� � 1\n");
		printf("(-1) ���������� ����������\n");
		printf("������� ������� 1: ");
		scanf_s("%d", &x);
		printf("������� ������� 2: ");
		scanf_s("%d", &y);
		if (x == -1 || y == -1) break;
		if (x > num || y > num || x < 1 || y < 1) {
			printf("\n�� ����� �� ������� �������");
			printf("\n\n��� ����������� ������� ����� ������...");
			_getch();
			continue;
		}
		if (x == y) continue;
		G[x - 1][y - 1] = 1;
	}
}
//������� ������
void freeMatrix(int num) {
	for (int i = 0; i < num; i++) {
		free(G[i]);
	}
	free(G);
	free(numV);
}
//����� � �������
void DFS(int v, int total) {
	numV[v] = 0;
	comp.push_back(v);
	for (int i = 0; i < total; ++i) {
		if ((G[v][i] == 1 || G[i][v] == 1) && numV[i] == 1)
			DFS(i, total);
	}
}
//����� ���������
void findComponents(int num, FILE* f) {
	for (int i = 0; i < num; i++) {
		if (numV[i] == 1) {
			DFS(i, num);
			printf("����������: ");
			fprintf(f, "����������: ");
			for (int j = 0; j < comp.size(); j++) {
				printf(" %c", comp[j] + 97);
				fprintf(f, " %c", comp[j] + 97);
			}
			fprintf(f, "\n");
			for (int j = 0; j < num; j++) {
				numV[i] = 1;
			}
			comp.clear();
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int num = 0, v = 0, var = 0;

	while (var != 5) {
		system("cls");
		printf("\t����:\n\n"
			"��� - �� ������: 0\n"
			"����� �������: 1\n"
			"��������� ��������� �������: 2\n"
			"���������� �������: 3\n"
			"�����: 4\n"
			"> ");
		scanf_s("%d", &var);
		switch (var) {
		case 0:
			numberVershin(&num);
			break;
		case 1:
			printMatrix(num, v);
			break;
		case 2:
			srand(time(NULL));
			generateMatrix(num);
			break;
		case 3:
			scanfMatrix(num);
			break;
		case 4:
			freeMatrix(num);
			break;
		default:
			printf("\n������ ������ ���...");
			_getch();
			break;
		}
	}
}