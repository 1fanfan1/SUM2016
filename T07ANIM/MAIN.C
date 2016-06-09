/*FILE NAME: MAIN.C
 *PROGRAMMER: AS5
 *DATE: 08.06.2016
 *PURPOSE: WinApi
*/

#include <windows.h>

#include "VEC.H"

/* Begin of 'WinMain' function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  MATR m =
  {{
    {2, 0, 0, 0},
    {1, 2, 0, 0},
    {1, 1, 2, 0},
    {1, 1, 1, 2}
  }};
  DBL g;

  m = MatrIdentity();
  m = MatrTranslate(VecSet(1, 2, 3));
  m = MatrScale(VecSet(1, 2, 3));
  m = MatrRotateX(30);
  m = MatrRotateY(30);
  m = MatrRotateZ(30);
  m = MatrRotate(30, VecSet(1, 2, 3));
  m = MatrMulMatr(MatrRotateX(90), MatrScale(VecSet(2, 2, 2)));
  m = MatrInverse(m);
  g = MatrDeterm(m);
  m = MatrTranspose(m);

  return 0;
}/* Begin of 'WinMain' function */