/*Programa para calcular la inversa de una matriz
de dimension [n][n]*/

//Compilar con: gcc nom_program.c -o nom_program -lm

//Author: Rodrigo Parra Pascual

/*Librerias*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdio_ext.h>

/*Definiciones*/
#define NUMPARAMS 2

/*Declaraciones*/
void PreguntarDimension(int *dim_mat);
float **InicializarMatriz(int dim_mat);
void IngresarValores(float **matriz, int dim_mat);
void ImprimirMatriz(float **matriz, int dim_mat);
float DeterminanteMatriz(float **matriz, int dim_mat);
float **MatrizMenores(float **matriz, int dim_mat);
float **MatrizCofactores(float **matriz, int dim_mat);
float **MatrizAdj(float **matriz, int dim_mat);
float **MatrizInversa(float **matriz, float det, int dim_mat);
double EpsilonMaquina();
int CleanInput(void);

int main()
{
	float **matriz1, **mat_menores, **Cofact, **Adj, **mat_inv, DET;
	int dim_mtrz=0;

	PreguntarDimension(&dim_mtrz);
	matriz1=InicializarMatriz(dim_mtrz);
	IngresarValores(matriz1, dim_mtrz);

	printf("\n\nMatriz A:\n");
	ImprimirMatriz(matriz1,dim_mtrz);

	DET=DeterminanteMatriz(matriz1, dim_mtrz);
	if(fabs(DET) <= EpsilonMaquina())
	{
		printf("\nLa matriz es singular (***NO TIENE INVERSA***)\n\n");
	}
	else
	{
		if(dim_mtrz == 1)
		{
			printf("Matriz inversa:\n");
			printf("\t%f\n\n", 1.0 / DET);
		}
		else
		{
			mat_menores = MatrizMenores(matriz1, dim_mtrz);
			Cofact = MatrizCofactores(mat_menores, dim_mtrz);
			Adj = MatrizAdj(Cofact, dim_mtrz);
			mat_inv = MatrizInversa(Adj, DET, dim_mtrz);

			printf("\n\nMatriz de menores:\n");
			ImprimirMatriz(mat_menores, dim_mtrz);

			printf("\n\nMatriz de cofactores:\n");
			ImprimirMatriz(Cofact, dim_mtrz);

			printf("\n\nMatriz adjunta:\n");
			ImprimirMatriz(Adj, dim_mtrz);

			printf("\n\nMatriz inversa:\n");
			ImprimirMatriz(mat_inv, dim_mtrz);
		}
	}

	free(matriz1);
	free(mat_menores);
	free(Cofact);
	free(Adj);
	free(mat_inv);

	printf("\n\n");
	//system("pause"); //solo en Windows
	return 0;
}

void PreguntarDimension(int *dim_mat)
{
	char c;
	printf("\n\t** INVERSA DE UNA MATRIZ **");
	printf("\n-----------------------------------------------------\n");
	printf("Cual es la dimension de la matriz?: ");
	while(!(scanf("%d%c", dim_mat, &c) == NUMPARAMS && c == '\n') || *dim_mat <= 0)
	{
		printf("Ingrese solo valor numerico entero mayor que cero, intente nuevamente.\n");
		printf("Cual es la dimension de la matriz?: ");
		CleanInput();
	}
}

float **InicializarMatriz(int dim_mat)
{
	float **arreglo;
	arreglo = (float **)calloc(dim_mat, sizeof(float *));
	if(arreglo == NULL)
	{
		printf("NO SE PUEDE ASIGNAR MEMORIA.\n");
		exit(1);
	}
	for(register int m = 0; m < dim_mat; m++)
	{
		arreglo[m]=(float *)calloc(dim_mat, sizeof(float));
		if(arreglo == NULL)
		{
			printf("NO SE PUEDE ASIGNAR MEMORIA.\n");
			exit(1);
		}
	}
	return arreglo;
}

void IngresarValores(float **matriz, int dim_mat)
{
	char c;
	printf("\n\nIngresa los valores de la MATRIZ\n");
	for(register int i = 0; i < dim_mat; i++)
	{
		for(register int j = 0; j < dim_mat; j++)
		{
			printf("Matriz: Elemento[%d][%d]: ", i+1, j+1);
			while(!(scanf("%f%c", &matriz[i][j], &c) == NUMPARAMS && c == '\n'))
			{
				printf("Introducir unicamente valor numerico, intente nuevamente.\n");
				printf("Matriz: Elemento[%d][%d]: ", i+1, j+1);
				CleanInput();
			}
		}
	}
}

void ImprimirMatriz(float **matriz, int dim_mat)
{
	for(register int i = 0; i < dim_mat; i++)
	{
		for(register int j = 0; j < dim_mat; j++)
		{
			printf("\t%f", matriz[i][j]);
		}
		printf("\n");
	}
}

float DeterminanteMatriz(float **matriz, int dim_mat)
{
  float **submatriz, det = 0;
  register int aux_fil = 0, aux_col = 0;
  submatriz = InicializarMatriz(dim_mat - 1);
  if(dim_mat == 1)
  {
    det = matriz[0][0];
  }
  else
  {
    for(register int col = 0; col < dim_mat; col++)
    {
      aux_fil=0; aux_col=0;
      for(register int i = 0; i < dim_mat; i++)
      {
        for(register int j = 0; j < dim_mat; j++)
        {
          if(i != 0 && j != col)
          {
            submatriz[aux_fil][aux_col] = matriz[i][j];
            aux_col++;
            if(aux_col >= dim_mat - 1)
            {
              aux_fil++;
              aux_col = 0;
            }
          }
        }
      }
      det+=pow(-1, col) * matriz[0][col] * DeterminanteMatriz(submatriz, dim_mat - 1);
    }
  }
  free(submatriz);
  return det;
}

float **MatrizMenores(float **matriz, int dim_mat)
{
	float **submatriz1, **menores;
	register int n_fil = 0, n_col = 0/*n_DIM = DIM - 1*/;
	submatriz1 = InicializarMatriz(dim_mat - 1);
	menores = InicializarMatriz(dim_mat);
	for(register int fil = 0; fil < dim_mat; fil++)
	{
		for(register int col = 0; col < dim_mat; col++)
		{
			n_fil = 0; n_col = 0;
			for(register int i = 0; i < dim_mat; i++)
			{
				for(register int j = 0; j < dim_mat; j++)
				{
					if(i != fil && j != col)
					{
						submatriz1[n_fil][n_col] = matriz[i][j];
						n_col++;
						if(n_col >= dim_mat - 1)
						{
						  n_fil++;
						  n_col = 0;
						}
					}
				}
			}
			menores[fil][col] = DeterminanteMatriz(submatriz1, dim_mat - 1);
		}
	}
	free(submatriz1);
	return menores;
}

float **MatrizCofactores(float **matriz, int dim_mat)
{
	float **cofactores;
	cofactores = InicializarMatriz(dim_mat);
	for(register int i = 0; i < dim_mat; i++)
	{
		for(register int j = 0; j < dim_mat; j++)
		{
			if(matriz[i][j] != 0.0)
				cofactores[i][j] = pow(-1.0, i + j) * matriz[i][j];
			else
				cofactores[i][j] = matriz[i][j];
		}
	}
	return cofactores;
}

float **MatrizAdj(float **matriz, int dim_mat)
{
	float **adjunta;
	adjunta = InicializarMatriz(dim_mat);
	for(register int i = 0; i < dim_mat; i++)
	{
		for(register int j = 0; j < dim_mat; j++)
		{
			adjunta[i][j] = matriz[j][i];
		}
	}
	return adjunta;
}

float **MatrizInversa(float **matriz, float det, int dim_mat)
{
	float **inversa;
	inversa = InicializarMatriz(dim_mat);
	for(register int i = 0; i < dim_mat; i++)
	{
		for(register int j = 0; j < dim_mat; j++)
		{
			inversa[i][j] = (1.0 / det) * matriz[i][j];
		}
	}
	return inversa;
}

double EpsilonMaquina()
{
  double eps = 1.0;
  while(1.0 + (eps * 0.5) > 1.0)
  {
    eps *= 0.5;
  }
  return eps;
}

int CleanInput(void)
{
	__fpurge(stdin);
	return 0;
}