/*Shvetz Andrei 10-5 07.08.2015*/
/* FILE NAME: MAIN.c
 * PROGRAMMER: AS5
 * PURPOSE:function WinMAIN    */

#include "UNITS.H"
#define AS5_WND_CLASS_NAME "My window class"



LRESULT CALLBACK AS5_MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{    
  MINMAXINFO *MinMax;

  static BITMAP bm;
  static HBITMAP hBm;
  static HDC hMemDC;
  static INT h, w, flag = 1;
  HDC hDC;
  PAINTSTRUCT ps;
  SetDbgMemHooks();
  switch(Msg)
  {
  case WM_GETMINMAXINFO:
    MinMax = (MINMAXINFO *)lParam;
    MinMax -> ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
      return 0;

  case WM_CREATE:
    SetTimer(hWnd, 0, 10, NULL);
    AS5_Anim.cs = (CREATESTRUCT *)lParam;
    AS5_AnimInit(hWnd);
    return 0;

  case WM_ERASEBKGND:
    return 0;

  case WM_TIMER: 
    AS5_AnimRender();
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  case WM_MOUSEWHEEL:
    AS5_MOUSEWHEEL += (SHORT)HIWORD(wParam);
    return 0;

  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    AS5_AnimResize(w, h);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    AS5_AnimCopyFrame();
    EndPaint(hWnd, &ps);
    return 0;

  case WM_COMMAND:
    flag = !flag;
    return 0;

  case WM_DESTROY:
    AS5_AnimClose();
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} 


/* Main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;
  INT i, j;
  

  SetDbgMemHooks();
 
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = AS5_MyWindowFunc;
  wc.lpszClassName = AS5_WND_CLASS_NAME;
  
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL,"Error register window class","Error", MB_OK);
    return 0;
  }

  hWnd = CreateWindow(AS5_WND_CLASS_NAME,"© Shvetz Corporation, 2016",
                      WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT,CW_USEDEFAULT,
                      1000, 1000,
                      NULL,
                      NULL,
                      hInstance,
                      NULL);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
  i = 1, j = 1;
   
  /*AS5_AnimAddUnit(AS5_UnitCreateBall(i * (AS5_Anim.W / 3.0) + 100, j * (AS5_Anim.H / 4.0) + 100, 0 ));*/
  //for(i = 0; i < 4; i++)
  //  for(j = 0; j < 4; j++)  
  AS5_AnimAddUnit(AS5_UnitCreateCube(0, 0, 0));
 
  //AS5_AnimAddUnit(AS5_UnitCreateCity(i * (AS5_Anim.W / 3.0) + 100, j * (AS5_Anim.H / 4.0) + 100, 0));
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
} /* End of Main function */

/* End of file "MAIN.c" */