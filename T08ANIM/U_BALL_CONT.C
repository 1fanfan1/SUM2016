/* FILE NAME: U_BALL_CONT.C
 * PROGRAMMER: AS5
 * DATE: 13.06.2016
 * PURPOSE: Control ball unit sample.
 */

#include "ANIM.H"

/* Ball unit representation type */
typedef struct
{
  as5UNIT;        /* Base unit fields */
  VEC Pos;        /* Ball position */
  VEC Shift;      /* Ball shift position */
  DBL TimerShift; /* Timer shift phase value*/
  DBL TimerSpeed; /* Timer speed value*/
  COLORREF Color; /* Color */
} as5UNIT_BALL_CONT;

/* Unit ball initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT_BALL *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static INT bX = 0, bY = 0;

static VOID AS5_UnitInit( as5UNIT_BALL_CONT *Uni, as5ANIM *Ani )
{
  Uni->Pos = VecSet(bX, bY, 0);
  Uni->Color = RGB(100, 100, 100);
} /* End of 'AS5_UnitInit' function */

/* Unit ball inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT_BALL *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AS5_UnitResponse( as5UNIT_BALL_CONT *Uni, as5ANIM *Ani )
{
  if ((bX + 10.0 * Ani->JX < Ani->W || bX - 10.0 * Ani->JX > 0) &&
      (bY + 10.0 * Ani->JY < Ani->H || bY - 10.0 * Ani->JY > 0))
  {
    bX += 30.0 * Ani->JX;
    bY += 30.0 * Ani->JY;
  }
  
  Uni->Shift = VecSet(bX, bY, 0);

  if (Ani->JBut[1])
    bX = Ani->W / 2, bY = Ani->H / 2;
} /* End of 'AS5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT_BALL *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AS5_UnitRender( as5UNIT_BALL_CONT *Uni, as5ANIM *Ani )
{
  VEC p = VecAddVec(Uni->Pos, Uni->Shift);
  
  SetDCBrushColor(Ani->hDC, Uni->Color);
  Ellipse(Ani->hDC, p.X - 20, p.Y - 20, p.X + 20, p.Y + 20);
} /* End of 'AL5_UnitRender' function */

/* Unit cube creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (as5UNIT *) pointer to created unit.
 */
as5UNIT * AS5_UnitCreateBallCont( VOID )
{
  as5UNIT_BALL_CONT *Uni;

  if ((Uni = (as5UNIT_BALL_CONT *)AS5_AnimUnitCreate(sizeof(as5UNIT_BALL_CONT))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AS5_UnitInit;
  Uni->Response = (VOID *)AS5_UnitResponse;
  Uni->Render = (VOID *)AS5_UnitRender;

  return (as5UNIT *)Uni;
} /* End of 'AS5_UnitCreateCube' function */

/* END OF 'U_BALL_CONT.C' FILE */
