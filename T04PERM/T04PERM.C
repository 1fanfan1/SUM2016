/*FILE NAME: T04PERM.C
 *PROGRAMMER: SA
 *DATE: 04.06.2016
 *PURPOSE: WinApi
*/

#include <stdio.h>
#define N 3
int P[N];
char parity = 1;


void Go( int Pos );
void SavePerm( void );
void Swap( int *A, int *B );

void main( void )
{
  int i;
  for (i = 0; i < N; i++)
    P[i] = i + 1;
  Go(0);    
}

void Go( int Pos )
{
  int i;
  if (Pos == N)
  {
    SavePerm();
    return;
  }
  else
  {
    for (i = Pos; i < N; i++)
    {
      if (Pos != i)
      {
        parity = !parity;
        Swap(&P[Pos], &P[i]);
      }
      Go(Pos + 1);
      if (Pos != i)
      {
        parity = !parity;
        Swap(&P[Pos], &P[i]);
      }
    }
  }
}

void SavePerm( void )
{
  FILE *F;
  int i;
  F = fopen("perm.log", "a");

  if (F == NULL)
    return;

  for (i = 0; i < N; i++)
    fprintf(F, "%2i ", P[i]);
  if (parity == 0)
    fprintf(F, "Odd\n");
  else
    fprintf(F, "Even\n");
  fclose(F);
}

void Swap( int *A, int *B )
{
  int tmp = *A;
  *A = *B;
  *B = tmp;
}