#include "ANIM.H"

VOID AS5_RndPrimDraw( as5PRIM *Pr );
typedef struct
{
  as5UNIT;
  VEC Pos;
  as5PRIM p;
}as5CUBE;

as5ANIM AS5_Anim;
/*
as5VERTEX CubeP[] =
{
  {{-1, -1,  1}},
  {{ 1, -1,  1}},
  {{ 1, -1, -1}},
  {{-1, -1, -1}},
  {{-1,  1,  1}},
  {{ 1,  1,  1}},
  {{ 1,  1, -1}},
  {{-1,  1, -1}}
};

INT CubeE[] =
{
  0, 1, 1, 2, 2, 3, 3, 0,
  4, 5, 5, 6, 6, 7, 7, 4,
  0, 4, 1, 5, 2, 6, 3, 7
};

as5PRIM Cube =
{
  CubeP, sizeof(CubeP) / sizeof(CubeP[0]),
  CubeE, sizeof(CubeE) / sizeof(CubeE[0])
};
*/
static VOID AS5_UnitInit( as5CUBE *Uni, as5ANIM *Ani )
{
  AS5_RndPrimLoad(&Uni->p, "ufo.g3d"); 
} /* End of 'AS5_UnitInit' function */

static VOID AS5_UnitRender( as5CUBE *Uni, as5ANIM *Ani )
{
  AS5_RndMatrWorld = MatrMulMatr(AS5_RndMatrWorld, MatrScale(VecSet(0.3, 0.3, 0.3)));
  AS5_RndMatrWorld = MatrMulMatr(AS5_RndMatrWorld, MatrRotateY(20 * AS5_Anim.GlobalTime));
  AS5_RndMatrWorld = MatrMulMatr(AS5_RndMatrWorld, MatrRotateX(6 * sin(AS5_Anim.GlobalTime)));
  AS5_RndMatrWorld = MatrMulMatr(AS5_RndMatrWorld, MatrRotateZ(6 * cos(AS5_Anim.GlobalTime)));
  AS5_RndPrimDraw(&Uni->p);
}

static VOID AS5_UnitClose( as5CUBE *Uni, as5ANIM *Ani )
{
  AS5_RndPrimFree(&Uni->p);
}


static VOID AS5_UnitResponse( as5CUBE *Uni, as5ANIM *Ani )
{
  
}

as5UNIT * AS5_UnitCreateCube( FLT x, FLT y, FLT z )
{
  as5CUBE *Uni;

  if ((Uni = (as5CUBE *)AS5_AnimUnitCreate(sizeof(as5CUBE))) == NULL)
    return NULL;
  Uni->Pos = VecSet(x, y, z); 
  /* Setup unit methods */
  Uni->Init = (VOID *)AS5_UnitInit;
  Uni->Render = (VOID *)AS5_UnitRender;
  Uni->Response = (VOID *)AS5_UnitResponse;
  Uni->Close = (VOID *)AS5_UnitClose;
  return (as5UNIT *)Uni;
} /* End of 'AS5_UnitCreateCube' function */
