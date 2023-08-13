/*Solución a un sistema de ecuaciones por el método de cramer
Un sistema de la forma:

(a_11)*x_1 + (a_12)*x_2 + ... + (a_1n)*x_n = b_1
(a_21)*x_1 + (a_22)*x_2 + ... + (a_2n)*x_n = b_2
.             .           ...   ..       .     .
.             .           ...      ..    .     .
.             .           ...         .. .     .
(a_n1)*x_1 + (a_n2)*x_2 + ... + (a_nn)*x_n = b_n
*/

//Author: Rodrigo Parra Pascual

//Compilar con: gcc nom_program.c -o nom_program -lm

//Librerias
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdio_ext.h>

//Definiciones
#define NUMPARAMS 2

//Declaraciones
void PreguntarDimension(int *dim_mat, int *dim_vec);
double **InicializarMatriz(int fil, int col);
double *InicializarVector(int dim_vec);
void LlenarMatriz(double **matriz, int dim_mat);
void LlenarVector(double *vector, int dim_vec);
void ImprimirMatriz(double **matriz, int dim_mat);
void ImprimirVector(double *vector, int dim_vec);
double Determinante(double **matriz, int dim_mat);
double *Cramer(double **matriz, double *vector, int dim_mat, int dim_vec, double det);
double EpsilonMaquina();
int CleanInput(void);

int main()
{
  int DIM_MAT = 0, DIM_VEC = 0;
  double **matriz1, *vector1, *vec_sol, Det = 0;

  PreguntarDimension(&DIM_MAT, &DIM_VEC);
  matriz1 = InicializarMatriz(DIM_MAT, DIM_MAT);
  vector1 = InicializarVector(DIM_VEC);
  LlenarMatriz(matriz1, DIM_MAT);
  LlenarVector(vector1, DIM_VEC);

  printf("\n\nMatriz A:\n");
  ImprimirMatriz(matriz1, DIM_MAT);

  printf("\n\nVector b:\n");
  ImprimirVector(vector1, DIM_VEC);

  Det = Determinante(matriz1, DIM_MAT);

  if(fabs(Det) < EpsilonMaquina())
  {
    printf("\n\nLa matriz es singular, el sistema no tiene solución.\n\n");
  }
  else
  {
    vec_sol = Cramer(matriz1, vector1, DIM_MAT, DIM_VEC, Det);

    printf("\n\nVector X:\n");
    ImprimirVector(vec_sol, DIM_VEC);
    printf("\n\n");
  }

  free(matriz1);
  free(vector1);
  free(vec_sol);

  return 0;
}

void PreguntarDimension(int *dim_mat, int *dim_vec)
{
  char c;
  printf("\n\t** SOLUCION A UN SISTEMA DE ECUACIONES **");
	printf("\n\t\t\t** POR **");
	printf("\n\t\t** MÉTODO DE CRAMER **");
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

double **InicializarMatriz(int fil, int col)
{
  double **arreglo;
  arreglo = (double **)calloc(fil, sizeof(double *));
  if(arreglo == NULL)
  {
    printf("NO SE PUEDE ASIGNAR MEMORIA.\n");
    exit(1);
  }
  for(register int m = 0; m < col; m++)
  {
    arreglo[m] = (double *)calloc(col, sizeof(double));
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
  submatriz = InicializarMatriz(dim_mat - 1, dim_mat - 1);
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

double *Cramer(double **matriz, double *vector, int dim_mat, int dim_vec, double det)
{
  double **matriz_aux, *vector_sol, det_aux;
  matriz_aux = InicializarMatriz(dim_mat, dim_mat);
  vector_sol = InicializarVector(dim_vec);
  if(dim_mat == 1)
  {
    vector_sol[0] = vector[0] / matriz[0][0];
  }
  else
  {
    for(register int k = 0; k < dim_vec; k++)
    {
      det_aux = 0;
      for(register int i = 0; i < dim_mat; i++)
      {
        for(register int j = 0; j < dim_mat; j++)
        {
          matriz_aux[i][j] = matriz[i][j];
          if(j == k)
          {
            matriz_aux[i][j] = vector[i];
          }
        }
      }
      det_aux = Determinante(matriz_aux, dim_mat);
      if(det_aux != 0.0)
      	vector_sol[k] = det_aux / det;
      else
      	vector_sol[k] == 0.0;
    }
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