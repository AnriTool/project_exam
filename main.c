#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Пункт 2.func {
int **sum(int **matrix1, int **matrix2, int n) //создаем указатель на функцию, аргументами которого будут указатели на наши матрицы две ** потому что двумерные матрицы
{
	int i,j; //Переменные для цикла
	int **result;

	//Выделение памяти для результата
	result = (int**)malloc(n*sizeof(int*));
	for(i = 0; i < n; i++)
		result[i] = (int*)malloc(n*sizeof(int));
	//Вычесление(+)
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			result[i][j] = matrix1[i][j] + matrix2[i][j];
	//Возвращение result из функции
	return result;
}

int **mul(int **matrix1, int **matrix2, int n)
{
	int i,j,k,s; //Переменные для цикла и суммы
	int **result;

	//Выделение памяти для результата
	result = (int**)malloc(n*sizeof(int*));
	for(i = 0; i < n; i++)
		result[i] = (int*)malloc(n*sizeof(int));
	//Вычесление(*)
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			s = 0;
			for (k = 0; k<n; k++) {
				s += matrix1[i][k] * matrix2[k][j];
			}
			result[i][j] += s;
		}
	}
	//Возвращение result из функции
	return result;
}
//} Пункт 2.func


int main(int argc, char *argv[])
{
	FILE *in, *out;
	int n,i,j,r;	//n - размерность матриц, i,j - переменные цикла, r - переменная рандома
	int **matrix1, **matrix2, **summ, **mult, **refresh;
	int min = 999, nech = 0;

//Пункт 5.start {
	//инициальзация и начало отчета таймера
	time_t start,end;
	volatile long unsigned t;
	start = time(NULL);
//} Пункт 5.start


//Пункт 1 {
	in = fopen("input.txt","w");

	//Читаем размернотсь матрицы
	printf("Enter demensions \n");
	scanf("%d",&n);
	printf("\n");

	//Выделяем память для матриц
	matrix1 = (int**)malloc(n*sizeof(int*));
	matrix2 = (int**)malloc(n*sizeof(int*));
	for (i = 0; i < n; i++) {
		matrix1[i] = (int*)malloc(n*sizeof(int));
		matrix2[i] = (int*)malloc(n*sizeof(int));
	}

	//Заполняем массив случайными числами
	srand(time(NULL)); //задаём seed, основаный на системном времени
	fprintf(in,"%d\n",n); //записываем размерность массивов
	for (i = 0; i<n; i++) {
		for(j = 0; j < n; j++) {
			r = rand()%101; //записываем случайное число в r (диапазон от 0 до 100)
			fprintf(in,"%d ",r);
		}
		fprintf(in,"\n");
	}

	fprintf(in,"\n");//Делаем отступ для красивой записи двух массивов в файл

	//Повторяем чтоб получить вторую матрицу
	for (i = 0; i<n; i++) {
		for(j = 0; j < n; j++) {
			r = rand()%101;
			fprintf(in,"%d ",r);
		}
		fprintf(in,"\n");
	}
	//очистка + закрытие файла
	fclose(in);
	for(i = 0; i < n; i++) {
		free(matrix1[i]);
		free(matrix2[i]);
	}
	free(matrix1);
	free(matrix2);
	n = 0;
//}	Пункт 1


//Пункт 2 {
	in = fopen("input.txt","r");
	out = fopen("output.txt","w");

	fscanf(in,"%d",&n);

	//Выделение памяти
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

	//Чтение массивов с файла + //Вывод
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

//} Пункт 2


//Пункт 3{
	refresh = (int**)malloc(n*sizeof(int*));
	for (i = 0; i < n; i++) {
		refresh[i] = (int*)malloc(n*sizeof(int));
	}

	for(i = 0; i < n; i++) {
		for(j = 0; j < n ; j++)
			if (j%2 != 0) {                  //Если индекс у столбца - нечетный(т.к. начинаем отчет с 0го эллемента), то меняем местами предыдущий и нынешний
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
//} Пункт 3

// Пункт 4{

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (matrix1[i][j] < min)
				min = matrix1[i][j];
			if ((matrix1[i][j] % 2) != 0)
				nech++;
		}
	printf("Min in Matrix1 = %d\n\n",min);
	printf("Odd's in Matrix1 = %d\n\n",nech);
//} Пункт 4

//Закрытие файлов+очистка
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
//Пункт 5.end {
	end = time(NULL);
	printf("Time = %f\n", difftime(end, start));
//}	Пункт 5.end
	getch();
	return 0;
}
