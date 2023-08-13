/*Librerias*/
#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>

/*Definiciones*/
#define NUMPARAMS 2

/*Declaraciones*/
void AsignarDimension(int *fil1, int *col1, int *fil2, int *col2);
float **InicializarMatriz(int fil, int col);
void LlenarMatriz(float **matriz1, char *mat, int fil, int col);
void ImprimirMatriz(float **matriz1, char *mat, int fil, int col);
float **MultiplicarMatrices(float **matriz1, float **matriz2, int fil1, int col1, int col2);
int CleanInput(void);

int main()
{
	float **Matriz_A, **Matriz_B, **Resultado;
	int FIL1=0, COL1=0, FIL2=0, COL2=0;
	AsignarDimension(&FIL1, &COL1, &FIL2, &COL2);
	Matriz_A=InicializarMatriz(FIL1, COL1);
	Matriz_B=InicializarMatriz(FIL2, COL2);
	LlenarMatriz(Matriz_A, "Matriz A", FIL1, COL1);
	LlenarMatriz(Matriz_B, "Matriz B", FIL2, COL2);
	ImprimirMatriz(Matriz_A, "Matriz A", FIL1, COL1);
	ImprimirMatriz(Matriz_B, "Matriz B", FIL2, COL2);
	Resultado=MultiplicarMatrices(Matriz_A, Matriz_B, FIL1, COL1, COL2);
	ImprimirMatriz(Resultado, "Matriz C=A*B", FIL1, COL2);
	free(Matriz_A);
	free(Matriz_B);
	free(Resultado);
	return 0;
}

void AsignarDimension(int *fil1, int *col1, int *fil2, int *col2)
{
	char c;
	printf("->INGRESAR DIMENSIONES DE LA MATRIZ A\n");
	printf("Numero de renglones: ");
	while(!(scanf("%d%c", fil1, &c)==NUMPARAMS && c=='\n') || *fil1<=0)
	{
		printf("\nIngrese valor numerico mayor que cero.\n");
		printf("Intente nuevamente.\n");
		printf("Numero de renglones: ");
		CleanInput();
	}
	printf("Numero de columnas: ");
	while(!(scanf("%d%c", col1, &c)==NUMPARAMS && c=='\n') || *col1<=0)
	{
		printf("\nIngrese valor numerico mayor que cero.\n");
		printf("Intente nuevamente.\n");
		printf("Numero de columnas: ");
		CleanInput();
	}
	
	printf("\n->INGRESAR DIMENSIONES DE LA MATRIZ B\n");
	do
	{
		printf("Numero de renglones: ");
		while(!(scanf("%d%c", fil2, &c)==NUMPARAMS && c=='\n') || *fil2<=0)
		{
			printf("Ingrese valor numerico mayor que cero.\n");
			printf("Intente nuevamente.\n");
			printf("Numero de renglones: ");
			CleanInput();
		}
		if(*fil2 != *col1)
		{
			printf("\nWarning: El numero de renglones de la matriz A debe ser\n");
			printf("exactamente igual al numero de columnas de la matriz B.\n");
		}
	}while(*fil2 != *col1);
	printf("Numero de columnas: ");
	while(!(scanf("%d%c", col2, &c)==NUMPARAMS && c=='\n') || *col2<=0)
	{
		printf("\nIngrese valor numerico mayor que cero.\n");
		printf("Intente nuevamente.\n");
		printf("Numero de columnas: ");
		CleanInput();
	}
}

float **InicializarMatriz(int fil, int col)
{
	float **arreglo;
	arreglo=(float **)calloc(fil, sizeof(float *));
	if(arreglo == NULL)
	{
		printf("NO SE PUEDE ASIGNAR MEMORIA\n");
		exit(1);
	}
	for(int m=0; m<fil; m++)
	{
		arreglo[m]=(float *)calloc(col, sizeof(float));
		if(arreglo[m] == NULL)
		{
			printf("NO SE PUEDE ASIGNAR MEMORIA\n");
			exit(1);
		}
	}
	return arreglo;
}

void LlenarMatriz(float **matriz1, char *mat, int fil, int col)
{
	char c;
	printf("\n->LLENAR %s\n", mat);
	for(int i=0; i<fil; i++)
	{
		for(int j=0; j<col; j++)
		{
			printf("Elemento[%d][%d]: ", i+1, j+1);
			while(!(scanf("%f%c", &matriz1[i][j], &c)==NUMPARAMS && c=='\n'))
			{
				printf("Ingrese valor numerico mayor que cero.\n");
				printf("Intente nuevamente.\n");
				printf("Elemento[%d][%d]: ", i+1, j+1);
				CleanInput();
			}
		}
	}
}

void ImprimirMatriz(float **matriz1, char *mat, int fil, int col)
{
	printf("\n->%s:\n", mat);
	for(int i=0; i<fil; i++)
	{
		for(int j=0; j<col; j++)
		{
			printf("%f\t", matriz1[i][j]);
		}
		printf("\n");
	}
}

float **MultiplicarMatrices(float **matriz1, float **matriz2, int fil1, int col1, int col2)
{
	float **producto;
	producto=InicializarMatriz(fil1, col2);
	for(int i=0; i<fil1; i++)
	{
		for(int j=0; j<col1; j++)
		{
			for(int k=0; k<col2; k++)
			{
				producto[i][k]+=matriz1[i][j]*matriz2[j][k];
			}
		}
	}
	return producto;
}

int CleanInput(void)
{
	__fpurge(stdin);
	return 0;
}