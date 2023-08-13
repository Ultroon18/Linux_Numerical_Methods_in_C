#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdio_ext.h>

#define NUMPARAMS 2

void PreguntarDimension(int *dim);
double **InicializarMatriz(int dim);
void LlenarMatriz(double **matriz, int dim);
void ImprimirMatriz(double **matriz, int dim);
double Determinante(double **matriz, int dim);
void ImprimirDeterminante(double *det);
int CleanInput();

int main()
{
	double **matriz, determinante;
	int dim_mtrz = 0;

	PreguntarDimension(&dim_mtrz);
	matriz = InicializarMatriz(dim_mtrz);
	LlenarMatriz(matriz, dim_mtrz);
	ImprimirMatriz(matriz, dim_mtrz);
	determinante = Determinante(matriz, dim_mtrz);
	ImprimirDeterminante(&determinante);

	return 0;
}


void PreguntarDimension(int *dim)
{
	char c;
	printf("\n\n\t\t--CALCULAR EL DETERMINANTE DE UNA MATRIZ--\n");
	printf("\nCual es la dimension de la matriz?: ");
	while(!(scanf("%d%c", dim, &c) == NUMPARAMS && c == '\n') || *dim <= 0)
	{
		printf("\nIngrese solo valores mayores que cero.\n");
		printf("Cual es la dimension de la matriz?: ");
		CleanInput();
	}
}

double **InicializarMatriz(int dim)
{
	double **arreglo;
	arreglo = (double **)calloc(dim, sizeof(double *));
	if(arreglo == NULL)
	{
		printf("\n¡No se puede asignar memoria!\n");
		exit(1);
	}
	for(register int i = 0; i < dim; i++)
	{
		arreglo[i] = (double *)calloc(dim, sizeof(double));
		if(arreglo == NULL)
        	{
                	printf("\n¡No se puede asignar memoria!\n");
                	exit(1);
        	}
	}
	return arreglo;
}

void LlenarMatriz(double **matriz, int dim)
{
	char c;
	printf("\nIngresa los valores de la matriz:\n");
	for(register int i = 0; i < dim; i++)
	{
		for(register int j = 0; j < dim; j++)
		{
			printf("Elemento[%d][%d]: ", i+1, j+1);
			while(!(scanf("%lf%c", &matriz[i][j], &c) == NUMPARAMS && c == '\n'))
			{
				printf("\nIngrese solo valores numericos.\n");
				printf("Elemento[%d][%d]: ", i+1, j+1);
				CleanInput();
			}
		}
	}
}

void ImprimirMatriz(double **matriz, int dim)
{
	printf("\n\nMatriz: \n");
	for(register int i = 0; i < dim; i++)
	{
		for(register int j = 0; j < dim; j++)
		{
			printf("%lf\t", matriz[i][j]);
		}
		printf("\n");
	}
}

double Determinante(double **matriz, int dim)
{
	double **submatriz, det = 0;
	int aux_fil = 0, aux_col = 0;
	submatriz = InicializarMatriz(dim - 1);
	if(dim == 1)
	{
		det = matriz[0][0];
	}
	else if(dim == 2)
	{
		det = matriz[0][0]*matriz[1][1] - matriz[0][1]*matriz[1][0];
	}
	else
	{
		for(register int col = 0; col < dim; col++)
		{
			aux_fil = 0;
			aux_col = 0;
			for(register int i = 0; i < dim; i++)
			{
				for(register int j = 0; j < dim; j++)
				{
					if(i != 0 && j != col)
					{
						submatriz[aux_fil][aux_col] = matriz[i][j];
						aux_col++;
						if(aux_col >= dim - 1)
						{
							aux_fil++;
							aux_col = 0;
						}
					}
				}
			}
			det += pow(-1, col) * matriz[0][col] * Determinante(submatriz, dim - 1);
		}
	}
	return det;

}

void ImprimirDeterminante(double *det)
{
	printf("\n\nDeterminante = %lf\n\n", *det);
}

int CleanInput()
{
	__fpurge(stdin);
	return 0;
}