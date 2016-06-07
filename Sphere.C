  /*FILE NAME: Sphere.C
 *PROGRAMMER: AS5
 *DATE: 07.06.2016
 *PURPOSE: WinApi
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "Sphere.h"

#pragma warning(disable: 4244)

#define PI 3.14159265358979323846
#define N 15
#define M 30
#define R 200

typedef double DBL;

typedef struct
{
  DBL X, Y, Z;
} VEC;

VEC ROT( VEC V, DBL Angle )
{
  VEC r;
  DBL A = Angle * PI / 180;
  
  r.X = V.X;
  r.Y = V.Y * cos(A) - V.Z * sin(A);
  r.Z = V.Y * sin(A) + V.Z * cos(A);
  
  return r;
}

VOID DrawSphere( HDC hDC, INT Xc, INT Yc )
{
  INT i, j, x, y;
  DOUBLE theta, phi, phase = clock() / 100;
  static VEC G[N][M];

  for (i = 0; i < N; i++)
  { 
    theta = i * PI / (N - 1);
    for (j = 0; j < M; j++)
    {
      phi = j * 2 * PI / (M - 1) + phase;
      
      G[i][j].X = R * sin(theta) * cos(phi);
      G[i][j].Y = R * sin(theta) * sin(phi);
      G[i][j].Z = R * cos(theta);

      G[i][j] = ROT(G[i][j], 30 * sin(phase));
    }
  }

  for (i = 0; i < N; i++)
  { 
    x = Xc + G[i][0].X;
    y = Yc - G[i][0].Z;
    MoveToEx(hDC, x , y, NULL);
    for (j = 1; j < M; j++)
    {
      x = Xc + G[i][j].X;
      y = Yc - G[i][j].Z;
      
      LineTo(hDC, x, y);
    }
  }
  for (j = 0; j < M; j++)
  { 
    x = Xc + G[0][j].X;
    y = Yc - G[0][j].Z;
    MoveToEx(hDC, x , y, NULL);
    for (i = 1; i < N; i++)
    {
      x = Xc + G[i][j].X;
      y = Yc - G[i][j].Z;
      LineTo(hDC, x, y);
    }
  }

}

