/* FILE NAME: U_CUBE.C
 * PROGRAMMER: AS5
 * DATE: 13.06.2016
 * PURPOSE: Control ball unit sample.
 */

#include "ANIM.H"

VEC CubeP[] =
{
  {-1, -1,  1},
  { 1, -1,  1},
  { 1, -1, -1},
  {-1, -1, -1},
  {-1,  1,  1},
  { 1,  1,  1},
  { 1,  1, -1},
  {-1,  1, -1}
};

INT CubeE[][2] =
{
  {0, 1}, {1, 2}, {2, 3}, {3, 0},
  {4, 5}, {5, 6}, {6, 7}, {7, 4},
  {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

as5PRIM Cube =
{
  CubeP, sizeof(CubeP) / sizeof(CubeP[0]),
  CubeE, sizeof(CubeE) / sizeof(CubeE[0])
};

/* Cube unit representation type */
typedef struct
{
  as5UNIT;        /* Base unit fields */
  VEC Pos;        /* Ball position */
  VEC Shift;      /* Ball shift position */
  DBL TimerShift; /* Timer shift phase value*/
  DBL TimerSpeed; /* Timer speed value*/
  COLORREF Color; /* Color */
} as5UNIT_CUBE;

/* Unit ball initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT_CUBE *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static INT bX = 0, bY = 0;

static VOID AS5_UnitInit( as5UNIT_CUBE *Uni, as5ANIM *Ani )
{
  Uni->Pos = VecSet(bX, bY, 0);
  Uni->Color = RGB(100, 100, 100);
} /* End of 'AS5_UnitInit' function */

/* Unit cube inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT_CUBE *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AS5_UnitResponse( as5UNIT_CUBE *Uni, as5ANIM *Ani )
{
 
} /* End of 'AS5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT_CUBE *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AS5_UnitRender( as5UNIT_CUBE *Uni, as5ANIM *Ani )
{
  
} /* End of 'AL5_UnitRender' function */

/* Unit cube creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (as5UNIT *) pointer to created unit.
 */
as5UNIT * AS5_UnitCreateCube( VOID )
{
 as5UNIT_CUBE *Uni;

  if ((Uni = (as5UNIT_CUBE *)AS5_AnimUnitCreate(sizeof(as5UNIT_CUBE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AS5_UnitInit;
  Uni->Response = (VOID *)AS5_UnitResponse;
  Uni->Render = (VOID *)AS5_UnitRender;

  return (as5UNIT *)Uni;
} /* End of 'AS5_UnitCreateCube' function */

/* End of 'U_CUBE.C' file */