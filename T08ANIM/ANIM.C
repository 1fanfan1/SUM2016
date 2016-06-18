/*Shvetz Andrei 10-5 07.08.2015*/
/* FILE NAME: ANIM.c
 * PROGRAMMER: AS5
 * PURPOSE:function anim    */

#include "ANIM.H"
#include <stdio.h>
#pragma comment(lib, "winmm")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")
#define AS5_GET_JOYSTIC_AXIS(A)  (2.0 * (ji.dw##A##pos - jc.w##A##min) / (jc.w##A##max - jc.w##A##min - 1) - 1)


INT AS5_MOUSEWHEEL;
as5ANIM AS5_Anim;
UINT AS5_RndPrg;

static UINT64
  AS5_StartTime,    /* Start program time */
  AS5_OldTime,      /* Time from program start to previous frame */
  AS5_OldTimeFPS,   /* Old time FPS measurement */
  AS5_PauseTime,    /* Time during pause period */
  AS5_TimePerSec,   /* Timer resolution */
  AS5_FrameCounter; /* Frames counter */

VOID AS5_AnimInit( HWND hWnd )
{ 
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};

  LARGE_INTEGER t;

  AS5_Anim.NumOfUnits = 0;
  
  memset(&AS5_Anim, 0, sizeof(as5ANIM));
  AS5_Anim.hWnd = hWnd;
  AS5_Anim.hDC = GetDC(hWnd);

    /*** openGl ***/
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(AS5_Anim.hDC, &pfd);
  DescribePixelFormat(AS5_Anim.hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(AS5_Anim.hDC, i, &pfd);
    /* OpenGL init: setup rendering context */
  AS5_Anim.hGLRC = wglCreateContext(AS5_Anim.hDC);
  wglMakeCurrent(AS5_Anim.hDC, AS5_Anim.hGLRC);
  /* OpenGL init: setup extensions: GLEW library */
  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(AS5_Anim.hGLRC);
    ReleaseDC(AS5_Anim.hWnd, AS5_Anim.hDC);
    exit(0);
  }

    /*** init timer ***/
  QueryPerformanceFrequency(&t);
  AS5_TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  AS5_StartTime = AS5_OldTime = AS5_OldTimeFPS = t.QuadPart;
  AS5_PauseTime = 0;

  AS5_RndMatrProj = MatrFrustum(-1, 1, -1, 1, 1, 100);
  AS5_RndMatrWorld = MatrIdentity();
  AS5_RndMatrView  = MatrMulMatr(MatrIdentity(), MatrTranslate(VecSet(-1, -1, 0)));

  /* OpenGL specific initialization */
  glClearColor(0.3, 0.5, 0.7, 1);
  glEnable(GL_DEPTH_TEST );
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  AS5_RndPrg = AS5_RndShaderLoad("a");
}

VOID AS5_AnimResize( INT w,INT h )
{
  AS5_Anim.W = w;
  AS5_Anim.H = h;
  glViewport(0, 0, w, h);
  AS5_RndProj();
}

VOID AS5_AnimCopyFrame( VOID )
{
  SwapBuffers(AS5_Anim.hDC);
}

VOID AS5_AnimAddUnit( as5UNIT *Uni )
{
  if (AS5_Anim.NumOfUnits < AS5_MAX_UNITS)
  {
    AS5_Anim.Units[AS5_Anim.NumOfUnits++] = Uni; 
    Uni->Init(Uni, &AS5_Anim);
  }
}

VOID AS5_AnimClose( VOID )
{
  INT i;

  AS5_RndShaderFree(AS5_RndPrg);

  for (i = 0; i < AS5_Anim.NumOfUnits; i++)
  {
    AS5_Anim.Units[i]->Close(AS5_Anim.Units[i], &AS5_Anim);
    free(AS5_Anim.Units[i]);
  }
  /* Delete rendering context */
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(AS5_Anim.hGLRC);

  /* Delete GDI data */
  ReleaseDC(AS5_Anim.hWnd, AS5_Anim.hDC);
  DeleteDC(AS5_Anim.hDC);
  KillTimer(AS5_Anim.hWnd, 0);
  memset(&AS5_Anim, 0, sizeof(as5ANIM));
  PostQuitMessage(0);
}

VOID AS5_AnimRender( VOID )
{
  INT i;
  static FLT dx = 0, dy = 0, dz = 0;
  LARGE_INTEGER t;
  POINT pt;
  srand(1);

  /* Mouse wheel */
  AS5_Anim.Mdz = AS5_MOUSEWHEEL;
  AS5_Anim.Mz += AS5_MOUSEWHEEL;
  AS5_MOUSEWHEEL = 0;

  /* Mouse */
  GetCursorPos(&pt);
  ScreenToClient(AS5_Anim.hWnd, &pt);
  AS5_Anim.Mdx = pt.x - AS5_Anim.Mx;
  AS5_Anim.Mdy = pt.y - AS5_Anim.My;
  AS5_Anim.Mx = pt.x;
  AS5_Anim.My = pt.y;

  /*Keyboard*/
  GetKeyboardState(AS5_Anim.Keys);
  for ( i = 0; i < 256; i++ )
  {
    AS5_Anim.Keys[i] >>= 7;
    if (!AS5_Anim.OldKeys[i] && AS5_Anim.Keys[i])
      AS5_Anim.KeysClick[i] = 1;
    else
      AS5_Anim.KeysClick[i] = 0;
  }
  memcpy(AS5_Anim.OldKeys, AS5_Anim.Keys, 256);

  /* joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
          AS5_Anim.JBut[i] = (ji.dwButtons >> i) & 1;

        /* Axes */
        AS5_Anim.JX = AS5_GET_JOYSTIC_AXIS(X);
        AS5_Anim.JY = AS5_GET_JOYSTIC_AXIS(Y);
        AS5_Anim.JZ = AS5_GET_JOYSTIC_AXIS(Z);
        AS5_Anim.JR = AS5_GET_JOYSTIC_AXIS(R);

        /* Point of view */
        AS5_Anim.JPov = ji.dwPOV == 0xFFFF ? 0 : ji.dwPOV / 4500 + 1;
      }
    }
  }

  /*** Handle timer ***/
  AS5_FrameCounter++;
  QueryPerformanceCounter(&t);
  
  /* Global time */
  AS5_Anim.GlobalTime = (FLT)(t.QuadPart - AS5_StartTime) / AS5_TimePerSec;
  AS5_Anim.GlobalDeltaTime = (FLT)(t.QuadPart - AS5_OldTime) / AS5_TimePerSec;
  
  /* Time with pause */
  if (AS5_Anim.IsPause)
  {
    AS5_Anim.DeltaTime = 0;
    AS5_PauseTime += t.QuadPart - AS5_OldTime;
  }
  else
  {
    AS5_Anim.DeltaTime = AS5_Anim.GlobalDeltaTime;
    AS5_Anim.Time = (FLT)(t.QuadPart - AS5_PauseTime - AS5_StartTime) / AS5_TimePerSec;
  }

  /* FPS */
  if (t.QuadPart - AS5_OldTimeFPS > AS5_TimePerSec)
  {
    CHAR str[100];

    AS5_Anim.FPS = AS5_FrameCounter * AS5_TimePerSec /
                                         (FLT)(t.QuadPart - AS5_OldTimeFPS);
    AS5_OldTimeFPS = t.QuadPart;
    AS5_FrameCounter = 0;
    sprintf(str, "Anim FPS: %.5f Mouse Coord:  %i, %i JoyStick Coord: %f %f", AS5_Anim.FPS, AS5_Anim.Mx, AS5_Anim.My, AS5_Anim.JX ,AS5_Anim.JY);
    SetWindowText(AS5_Anim.hWnd, str);
  }
  AS5_OldTime = t.QuadPart;

  for (i = 0; i < AS5_Anim.NumOfUnits; i++)  
    AS5_Anim.Units[i]->Response(AS5_Anim.Units[i], &AS5_Anim);
   /*** Clear frame ***/
  /* Clear background */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (i = 0; i < AS5_Anim.NumOfUnits; i++)  
  {
    AS5_RndMatrWorld = MatrIdentity();
    AS5_Anim.Units[i]->Render(AS5_Anim.Units[i], &AS5_Anim);
  }

  dx += AS5_Anim.JX;
  dy += AS5_Anim.JY;
  dz += AS5_Anim.JZ;
  AS5_RndMatrView = MatrView(VecSet(dx - 40, dy - 40, dz - 40), VecSet(5, 5, 5), VecSet(0, 1, 0));
  glLoadMatrixf(&AS5_RndMatrView.A[0][0]);
  glFinish();
}