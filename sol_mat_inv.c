/*
Programa para encontra la solucion a un sistema de ecuaciones
de dimension nxn por el metodo de matriz inversa.
Un sistema de la forma:

(a_11)*x_1 + (a_12)*x_2 + ... + (a_1n)*x_n = b_1
(a_21)*x_1 + (a_22)*x_2 + ... + (a_2n)*x_n = b_2
.             .           ...   ..       .     .
.             .           ...      ..    .     .
.             .           ...         .. .     .
(a_n1)*x_1 + (a_n2)*x_2 + ... + (a_nn)*x_n = b_n

x_n = inversa(A[n][n]) * vector(b[n][1])
*/

//Author: Rodrigo Parra Pascual

//Compilar con: gcc nom_prog.c -o nom_prog -lm

/*Librerias*/
#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<math.h>

/*Definiciones*/
#define NUMPARAMS 2

/*Declaraciones*/
void PreguntarDimension(int *dim_mat, int *dim_vec);
double **InicializarMatriz(int dim_mat);
double *InicializarVector(int dim_vec);
void LlenarMatriz(double **matriz, int dim_mat);
void LlenarVector(double *vector, int dim_vec);
void ImprimirMatriz(double **matriz, int dim_mat);
void ImprimirVector(double *vector, int dim_vec);
double Determinante(double **matriz, int dim_mat);
double **MatrizMenores(double **matriz, int dim_mat);
double **MatrizCofactores(double **matriz, int dim_mat);
double **MatrizAdj(double **matriz, int dim_mat);
double **MatrizInversa(double **matriz, double det, int dim_mat);
double *Solucion(double **matriz, double *vector2, int dim_vec, int dim_mat, double det);
double EpsilonMaquina();
int CleanInput(void);

int main()
{
	double **matriz1, **mat_menores, **Cofact, **Adj, **mat_inv, *vector1, *vec_sol, DET;
	int dim_mtrz=0, dim_vect = 0;

	PreguntarDimension(&dim_mtrz, &dim_vect);
	matriz1=InicializarMatriz(dim_mtrz);
	vector1 = InicializarVector(dim_vect);
	LlenarMatriz(matriz1, dim_mtrz);
	LlenarVector(vector1, dim_vect);

  	printf("\n\nMatriz A:\n");
	ImprimirMatriz(matriz1, dim_mtrz);

  	printf("\n\nVector b:\n");
	ImprimirVector(vector1, dim_vect);

	DET=Determinante(matriz1, dim_mtrz);
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
			vec_sol = Solucion(Adj, vector1, dim_vect, dim_mtrz, DET);

			printf("\n\nMatriz inversa:\n");
			ImprimirMatriz(mat_inv, dim_mtrz);

      printf("\n\nVector solucion:\n");
      ImprimirVector(vec_sol, dim_vect);
		}
	}

	free(matriz1);
	free(vector1);
	free(mat_menores);
	free(Cofact);
	free(Adj);
	free(mat_inv);
	free(vec_sol);

	printf("\n\n");
	//system("pause"); //solo en Windows
	return 0;
}

void PreguntarDimension(int *dim_mat, int *dim_vec)
{
  char c;
	printf("\n\t** SOLUCION A UN SISTEMA DE ECUACIONES **");
	printf("\n\t\t\t** POR **");
	printf("\n\t\t** INVERSA DE UNA MATRIZ **");
	printf("\n-----------------------------------------------------\n");
  printf("Cuál es la dimensión de la matriz? ");
  while(!(scanf("%d%c",dim_mat, &c) == NUMPARAMS && c == '\n') || *dim_mat <= 0)
  {
    printf("Ingrese solo valor numérico mayor que cero, intente nuevamente.\n");
    printf("Cuál es la dimensión de la matriz? ");
    CleanInput();
  }
  do
  {
    printf("Cuál es la dimensión del vector? ");
    while(!(scanf("%d%c",dim_vec, &c) == NUMPARAMS && c == '\n') || *dim_vec <= 0)
    {
      printf("Ingrese solo valor numérico mayor que cero, intente nuevamente.\n");
      printf("Cuál es la dimensión del vector? ");
      CleanInput();
    }
    if(*dim_vec != *dim_mat)
    {
      printf("La dimensión del vector debe ser igual a la dimensión de la matriz.\n");
    }
  }while(*dim_vec != *dim_mat);
}

double **InicializarMatriz(int dim_mat)
{
  double **arreglo;
  arreglo = (double **)calloc(dim_mat, sizeof(double *));
  if(arreglo == NULL)
  {
    printf("NO SE PUEDE ASIGNAR MEMORIA.\n");
    exit(1);
  }
  for(register int m = 0; m < dim_mat; m++)
  {
    arreglo[m] = (double *)calloc(dim_mat, sizeof(double));
    if(arreglo[m] == NULL)
    {
      printf("NO SE PUEDE ASIGNAR MEMORIA.\n");
      exit(1);
    }
  }
  return arreglo;
}

double *InicializarVector(int dim_vec)
{
  double *vector;
  vector = (double *)calloc(dim_vec, sizeof(double));
  if(vector == NULL)
  {
    printf("NO SE PUEDE ASIGNAR MEMORIA.\n");
    exit(1);
  }
  return vector;
}

void LlenarMatriz(double **matriz, int dim_mat)
{
  char c;
  printf("\n\nIngresa los valores de la matriz\n");
  for(register int i = 0; i < dim_mat; i++)
  {
    for(register int j = 0; j < dim_mat; j++)
    {
      printf("Matriz[%d][%d]: ", i+1, j+1);
      while(!(scanf("%lf%c", &matriz[i][j], &c) == NUMPARAMS && c == '\n'))
      {
        printf("Ingrese solo valor numérico, intente nuevamente.\n");
        printf("Matriz[%d][%d]: ", i+1, j+1);
        CleanInput();
      }
    }
  }
}

void LlenarVector(double *vector, int dim_vec)
{
  char c;
  printf("\n\nIngresa los valores del vector\n");
  for(register int i = 0; i < dim_vec; i++)
  {
    printf("Vector[%d]: ", i+1);
    while(!(scanf("%lf%c", &vector[i], &c) == NUMPARAMS && c == '\n'))
    {
      printf("Ingrese solo valor numérico, intente nuevamente.\n");
      printf("Vector[%d]: ", i+1);
      CleanInput();
    }
  }
}

void ImprimirMatriz(double **matriz, int dim_mat)
{
  for(register int i = 0; i < dim_mat; i++)
  {
    for(register int j = 0; j < dim_mat; j++)
    {
      printf("\t%lf", matriz[i][j]);
    }
    printf("\n");
  }
}

void ImprimirVector(double *vector, int dim_vec)
{
  for(register int i = 0; i < dim_vec; i++)
  {
    printf("\t%lf\n", vector[i]);
  }
}

double Determinante(double **matriz, int dim_mat)
{
  double **submatriz, det = 0;
  register int aux_fil, aux_col;
  submatriz = InicializarMatriz(dim_mat - 1);
  if(dim_mat == 1)
  {
    det = matriz[0][0];
  }
  else
  {
    for(register int col = 0; col < dim_mat; col++)
    {
      aux_fil = 0;
      aux_col = 0;
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
      det += pow(-1, col) * matriz[0][col] * Determinante(submatriz, dim_mat - 1);
    }
  }
  free(submatriz);
  return det;
}

double **MatrizMenores(double **matriz, int dim_mat)
{
	double **submatriz1, **menores;
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
			menores[fil][col] = Determinante(submatriz1, dim_mat - 1);
		}
	}
	free(submatriz1);
	return menores;
}

double **MatrizCofactores(double **matriz, int dim_mat)
{
	double **cofactores;
	cofactores = InicializarMatriz(dim_mat);
	for(register int i = 0; i < dim_mat; i++)
	{
		for(register int j = 0; j < dim_mat; j++)
		{
			cofactores[i][j] = pow(-1.0, i + j) * matriz[i][j];
		}
	}
	return cofactores;
}

double **MatrizAdj(double **matriz, int dim_mat)
{
	double **adjunta;
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

double **MatrizInversa(double **matriz, double det, int dim_mat)
{
	double **inversa;
	inversa = InicializarMatriz(dim_mat);
	for(register int i = 0; i < dim_mat; i++)
	{
		for(register int j = 0; j < dim_mat; j++)
		{
			if(matriz[i][j] != 0.0)
				inversa[i][j] = (1.0 / det) * matriz[i][j];
			else
				inversa[i][j] = matriz[i][j];
		}
	}
	return inversa;
}

double *Solucion(double **matriz, double *vector2, int dim_vec, int dim_mat, double det)
{
	double *vector_sol;
	vector_sol = InicializarVector(dim_vec);
	for(register int i = 0; i < dim_mat; i++)
	{
		for(register int j = 0; j < dim_mat; j++)
		{
			vector_sol[i] += matriz[i][j] * vector2[j];
		}
		if(vector_sol[i] != 0.0)
				vector_sol[i] = (1.0/det) * vector_sol[i];
	}
	return vector_sol;
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
