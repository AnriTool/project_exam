#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//����� 2.func {
int **sum(int **matrix1, int **matrix2, int n) //������� ��������� �� �������, ����������� �������� ����� ��������� �� ���� ������� ��� ** ������ ��� ��������� �������
{
	int i,j; //���������� ��� �����
	int **result;

	//��������� ������ ��� ����������
	result = (int**)malloc(n*sizeof(int*));
	for(i = 0; i < n; i++)
		result[i] = (int*)malloc(n*sizeof(int));
	//����������(+)
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			result[i][j] = matrix1[i][j] + matrix2[i][j];
	//����������� result �� �������
	return result;
}

int **mul(int **matrix1, int **matrix2, int n)
{
	int i,j,k,s; //���������� ��� ����� � �����
	int **result;

	//��������� ������ ��� ����������
	result = (int**)malloc(n*sizeof(int*));
	for(i = 0; i < n; i++)
		result[i] = (int*)malloc(n*sizeof(int));
	//����������(*)
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			s = 0;
			for (k = 0; k<n; k++) {
				s += matrix1[i][k] * matrix2[k][j];
			}
			result[i][j] += s;
		}
	}
	//����������� result �� �������
	return result;
}
//} ����� 2.func


int main(int argc, char *argv[])
{
	FILE *in, *out;
	int n,i,j,r;	//n - ����������� ������, i,j - ���������� �����, r - ���������� �������
	int **matrix1, **matrix2, **summ, **mult, **refresh;
	int min = 999, nech = 0;

//����� 5.start {
	//������������� � ������ ������ �������
	time_t start,end;
	volatile long unsigned t;
	start = time(NULL);
//} ����� 5.start


//����� 1 {
	in = fopen("input.txt","w");

	//������ ����������� �������
	printf("Enter demensions \n");
	scanf("%d",&n);
	printf("\n");

	//�������� ������ ��� ������
	matrix1 = (int**)malloc(n*sizeof(int*));
	matrix2 = (int**)malloc(n*sizeof(int*));
	for (i = 0; i < n; i++) {
		matrix1[i] = (int*)malloc(n*sizeof(int));
		matrix2[i] = (int*)malloc(n*sizeof(int));
	}

	//��������� ������ ���������� �������
	srand(time(NULL)); //����� seed, ��������� �� ��������� �������
	fprintf(in,"%d\n",n); //���������� ����������� ��������
	for (i = 0; i<n; i++) {
		for(j = 0; j < n; j++) {
			r = rand()%101; //���������� ��������� ����� � r (�������� �� 0 �� 100)
			fprintf(in,"%d ",r);
		}
		fprintf(in,"\n");
	}

	fprintf(in,"\n");//������ ������ ��� �������� ������ ���� �������� � ����

	//��������� ���� �������� ������ �������
	for (i = 0; i<n; i++) {
		for(j = 0; j < n; j++) {
			r = rand()%101;
			fprintf(in,"%d ",r);
		}
		fprintf(in,"\n");
	}
	//������� + �������� �����
	fclose(in);
	for(i = 0; i < n; i++) {
		free(matrix1[i]);
		free(matrix2[i]);
	}
	free(matrix1);
	free(matrix2);
	n = 0;
//}	����� 1


//����� 2 {
	in = fopen("input.txt","r");
	out = fopen("output.txt","w");

	fscanf(in,"%d",&n);

	//��������� ������
	matrix1 = (int**)malloc(n*sizeof(int*));
	matrix2 = (int**)malloc(n*sizeof(int*));
	mult = (int**)malloc(n*sizeof(int*));
	summ = (int**)malloc(n*sizeof(int*));
	for (i = 0; i < n; i++) {
		matrix1[i] = (int*)malloc(n*sizeof(int));
		matrix2[i] = (int*)malloc(n*sizeof(int));
		mult[i] = (int*)malloc(n*sizeof(int));
		summ[i] = (int*)malloc(n*sizeof(int));
	}

	//������ �������� � ����� + //�����
	printf("Matrix1\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(in,"%d", &matrix1[i][j]);
			printf("%d ",matrix1[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	printf("Matrix2\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(in,"%d", &matrix2[i][j]);
			printf("%d ",matrix2[i][j]);
		}
		printf("\n");
	}

	summ = sum(matrix1,matrix2,n);
	mult = mul(matrix1,matrix2,n);

	printf("\nSum\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ",summ[i][j]);
			fprintf(out,"%d ",summ[i][j]);
		}
		printf("\n");
		fprintf(out,"\n");
	}

	printf("\nMult\n");
	fprintf(out,"\n",n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ",mult[i][j]);
			fprintf(out,"%d ",mult[i][j]);
		}
		printf("\n");
		fprintf(out,"\n");
	}

//} ����� 2


//����� 3{
	refresh = (int**)malloc(n*sizeof(int*));
	for (i = 0; i < n; i++) {
		refresh[i] = (int*)malloc(n*sizeof(int));
	}

	for(i = 0; i < n; i++) {
		for(j = 0; j < n ; j++)
			if (j%2 != 0) {                  //���� ������ � ������� - ��������(�.�. �������� ����� � 0�� ���������), �� ������ ������� ���������� � ��������
				refresh[i][j-1] = summ[i][j];
				refresh[i][j] = summ[i][j-1];
			} else
				refresh[i][j] = summ[i][j];
	}

	printf("\nRefresh\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ",refresh[i][j]);
		}
		printf("\n");
	}
	printf("\n");
//} ����� 3

// ����� 4{

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (matrix1[i][j] < min)
				min = matrix1[i][j];
			if ((matrix1[i][j] % 2) != 0)
				nech++;
		}
	printf("Min in Matrix1 = %d\n\n",min);
	printf("Odd's in Matrix1 = %d\n\n",nech);
//} ����� 4

//�������� ������+�������
	for(i = 0; i < n; i++) {
		free(matrix1[i]);
		free(matrix2[i]);
		free(mult[i]);
		free(summ[i]);
		free(refresh[i]);
	}
	free(matrix1);
	free(matrix2);
	free(mult);
	free(summ);
	free(refresh);
	fclose(in);
	fclose(out);
//����� 5.end {
	end = time(NULL);
	printf("Time = %f\n", difftime(end, start));
//}	����� 5.end
	getch();
	return 0;
}
