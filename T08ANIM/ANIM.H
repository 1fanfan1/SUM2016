/*Shvetz Andrei 10-5 07.08.2015*/
/* FILE NAME: ANIM.H
 * PROGRAMMER: AS5
 * PURPOSE: main header of project    */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.H"

#include "IMAGE.h"
#include <time.h>

#define AS5_MAX_UNITS 100

  /* Timer data */

typedef struct tagas5UNIT as5UNIT;
typedef struct
{
  CREATESTRUCT *cs;
  HWND hWnd; //
  HDC hDC;   //
  INT W, H;  //
  HGLRC hGLRC;                   /* Rendering context */
  as5UNIT *Units[AS5_MAX_UNITS]; //
  INT NumOfUnits; //
  /*** Timer ***/
  FLT GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
      Time, DeltaTime,             /* Time with pause and interframe interval */
      FPS;                         /* Frames per seond value */
  BOOL IsPause;                     /* Pause flag */

    /***  Mouse   ***/
  INT Mdx, Mdy, Mdz,
      Mx,  My,  Mz;

  /*** KeyBoard ***/
  BYTE Keys[256], OldKeys[256], KeysClick[256];

  /*** JoyStick ***/
  BYTE JBut[32];                    /* Joystick button state */
  INT JPov;                      /* Joystick point-of-view control [0,1..8] */
  FLT JX, JY, JZ, JR;              /* Joystick axes */
} as5ANIM;


struct tagas5UNIT
{
  /* Unit initialization function.
   * ARGUMENTS:
   *   - self-pointer to unit object:
   *       as5UNIT *Uni;
   *   - animation context:
   *       as5ANIM *Ani;
   * RETURNS: None.
   */
  VOID (* Init)( as5UNIT *Uni, as5ANIM *Ani );

  /* Unit deinitialization function.
   * ARGUMENTS:
   *   - self-pointer to unit object:
   *       as5UNIT *Uni;
   *   - animation context:
   *       as5ANIM *Ani;
   * RETURNS: None.
   */
  VOID (* Close)( as5UNIT *Uni, as5ANIM *Ani );

  /* Unit inter frame events handle function.
   * ARGUMENTS:
   *   - self-pointer to unit object:
   *       as5UNIT *Uni;
   *   - animation context:
   *       as5ANIM *Ani;
   * RETURNS: None.
   */
  VOID (* Response)( as5UNIT *Uni, as5ANIM *Ani );

  /* Unit render function.
   * ARGUMENTS:
   *   - self-pointer to unit object:
   *       as5UNIT *Uni;
   *   - animation context:
   *       as5ANIM *Ani;
   * RETURNS: None.
   */
  VOID (* Render)( as5UNIT *Uni, as5ANIM *Ani );
};


typedef struct
{
  INT VA, VBuf, IBuf;
  INT NumOfI;       
} as5PRIM;

extern MATR AS5_RndMatrWorld/* = MatrIdentity()*/,
            AS5_RndMatrView /* = MatrMulMatr(MatrIdentity, MatrTranslate(VecSet(-1, -1, 0)))*/,
            AS5_RndMatrProj;
extern FLT  AS5_RndProjDist,
     AS5_RndFarClip,
     AS5_RndProjSize;
extern INT AS5_MOUSEWHEEL;
extern as5ANIM AS5_Anim;
extern UINT AS5_RndPrg;

VOID AS5_AnimInit( HWND hWnd );
VOID AS5_AnimResize( INT w,INT h );
VOID AS5_AnimCopyFrame( VOID );
VOID AS5_AnimAddUnit( as5UNIT *Uni );
VOID AS5_AnimClose( VOID );
VOID AS5_AnimRender( VOID );
VOID AS5_RndProj( VOID );
BOOL AS5_RndPrimLoad( as5PRIM *Pr, CHAR *FileName );
VOID AS5_RndPrimFree( as5PRIM *Pr );
as5UNIT * AS5_AnimUnitCreate( INT Size );
VOID AS5_RndShaderFree( UINT Prg );
UINT AS5_RndShaderLoad( CHAR *FileNamePrefix );

#endif /* __ANIM_H_ */
