/*Shvetz Andrei 10-5 07.08.2015*/
/* FILE NAME: UNITS.c
 * PROGRAMMER: AS5
 * PURPOSE: static Unit function   */

#include "ANIM.H"


#include "ANIM.H"





/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AS5_UnitInit( as5UNIT *Uni, as5ANIM *Ani )
{
} /* End of 'AS5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AS5_UnitClose( as5UNIT *Uni, as5ANIM *Ani )
{
} /* End of 'AS5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AS5_UnitResponse( as5UNIT *Uni, as5ANIM *Ani )
{
} /* End of 'AS5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       as5UNIT *Uni;
 *   - animation context:
 *       as5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AS5_UnitRender( as5UNIT *Uni, as5ANIM *Ani )
{
} /* End of 'AS5_UnitRender' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (as5UNIT *) pointer to created unit.
 */
as5UNIT * AS5_AnimUnitCreate( INT Size )
{
  as5UNIT *Uni;
  /* Memory allocation */
  if (Size < sizeof(as5UNIT) ||
      (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = AS5_UnitInit;
  Uni->Close = AS5_UnitClose;
  Uni->Response = AS5_UnitResponse;
  Uni->Render = AS5_UnitRender;
  return Uni;
} /* End of 'AS5_AnimUnitCreate' function */