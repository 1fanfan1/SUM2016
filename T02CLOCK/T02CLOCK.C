/*FILE NAME: T01EYES.C
 *PROGRAMMER: SA
 *DATE: 02.06.2016
 *PURPOSE: WinApi
*/

#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define M_PI       3.14159265358979323846

VOID Clock( HWND hWnd, HDC hDC, INT X, INT Y, INT R );
LRESULT CALLBACK MyWinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID Eyes( HWND hWnd, HDC hDC, INT X, INT Y, INT R, INT R1, DOUBLE ptx, DOUBLE pty );

/* Begin of 'WinMaim'*/
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hInstance = hInstance;
  wc.lpszClassName = "My Window Class";
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = MyWinFunc;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "ERROR REGISTER WINDOW CLASS", "ERROR", MB_OK);
    return 0;
  }

  hWnd = CreateWindow("My Window Class",
    "© Shvetz Corporation, 2016",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);

  return 0;
}  /* End of 'WinMaim'*/

/* Begin of 'MyWinFunc' function */
LRESULT CALLBACK MyWinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  HPEN hPen;
  PAINTSTRUCT ps;
  SYSTEMTIME Time;
  INT i, j;
  CHAR str[8];
  static INT w, h;
  static HDC hMemDC, hMemDCLogo;
  static HBITMAP hBm, hBmLogo;
  static BITMAP bm;
  double alpha, beta, gamma;
  
  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hBmLogo = LoadImage(NULL, "CLOCK.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hBmLogo, sizeof(bm), &bm);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCLogo = CreateCompatibleDC(hDC);
    SelectObject(hMemDCLogo, hBmLogo);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;
  case WM_TIMER:
    Rectangle(hMemDC, 0, 0, w + 1, h + 1);
    BitBlt(hMemDC, (w - bm.bmWidth) / 2, (h - bm.bmHeight) / 2, (w - bm.bmWidth) / 2 + bm.bmWidth, (h - bm.bmHeight) / 2 + bm.bmHeight, hMemDCLogo, 0, 0, SRCCOPY);

    GetLocalTime(&Time);
    
    alpha = (Time.wSecond + Time.wMilliseconds / 1000.0) * 2 *  M_PI / 60;
    beta = (Time.wMinute + Time.wSecond / 60.0) * 2 * M_PI / 60;
    gamma = (Time.wHour + Time.wMinute / 60.0) * 2 * M_PI / 12;
    SetDCPenColor(hMemDC, RGB(0, 0, 0)); 
    /* Seconds */
    hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hMemDC, hPen);
    MoveToEx(hMemDC, w / 2, h / 2, NULL);                
    LineTo(hMemDC, w / 2 + sin(alpha) * bm.bmWidth / 2, h / 2 - cos(alpha) * (bm.bmHeight / 2 - 20));
    DeleteObject(hPen);
    /* Minutes */
    hPen = CreatePen(PS_SOLID, 8, RGB(200, 200, 200));
    SelectObject(hMemDC, hPen);
    MoveToEx(hMemDC, w / 2, h / 2, NULL); 
    LineTo(hMemDC, w / 2 + sin(beta) * bm.bmWidth / 2, h / 2 - cos(beta) * (bm.bmHeight / 2 - 30));
    DeleteObject(hPen);
    /* Hours */
    hPen = CreatePen(PS_SOLID, 9, RGB(200, 100, 100));
    SelectObject(hMemDC, hPen);
    MoveToEx(hMemDC, w / 2, h / 2, NULL);                
    LineTo(hMemDC, w / 2 + sin(gamma) * bm.bmWidth / 2, h / 2 - cos(gamma) * (bm.bmHeight / 2 - 80));
    DeleteObject(hPen);
    /* Eyes */
    /*
    for (i = 0; i < (w - bm.bmWidth) / 2 - 25; i += 50)
      for (j = 0; j < h; j += 50)
        Eyes(hWnd, hMemDC, i, j, 25, 8, w / 2 + sin(alpha) * bm.bmWidth / 2, h / 2 - cos(alpha) * bm.bmHeight / 2);
    for (i = w; i > (w - bm.bmWidth) / 2 + bm.bmWidth + 25; i -= 50)
      for (j = 0; j < h; j += 50)
        Eyes(hWnd, hMemDC, i, j, 25, 8, w / 2 + sin(alpha) * bm.bmWidth / 2, h / 2 - cos(alpha) * bm.bmHeight / 2);
    */
    /* Output time */
    str[0] = Time.wHour / 10 + 48;
    str[1] = Time.wHour % 10 + 48;
    str[2] = 58;
    str[3] = Time.wMinute / 10 + 48;
    str[4] = Time.wMinute % 10 + 48;
    str[5] = 58;
    str[6] = Time.wSecond / 10 + 48;
    str[7] = Time.wSecond % 10 + 48;

    SelectObject(hMemDC, GetStockObject(DC_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    
    Ellipse(hMemDC, w / 2 - 20, h / 2 - 20, w / 2 + 20, h / 2 + 20);
    
    TextOut(hMemDC, w / 2 - 30, h - 210, str, 8);
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_MOUSEMOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    DeleteDC(hMemDC);
    DeleteObject(hBm);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}  /* End of 'MyWinFunc' function */

/* Begin of 'Eyes' function */
VOID Eyes( HWND hWnd, HDC hDC, INT X, INT Y, INT R, INT R1, DOUBLE ptx, DOUBLE pty )
{
  INT dx, dy;
  DOUBLE t;


  dx = (int)(ptx - X);
  dy = (int)(pty - Y);

  t = (R - R1) / sqrt(dx * dx + dy * dy);
  if (t < 1)
  {
    dx = (INT)(t * dx);
    dy = (INT)(t * dy);
  }
  
  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(0, 0, 0));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(200, 200, 150));

  Ellipse(hDC, X - R, Y - R, X + R, Y + R);

  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(0, 0, 0));
  SelectObject(hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 0, 0));

  Ellipse(hDC, X + dx - R1, Y + dy - R1, X + dx + R1, Y + dy + R1);
}  /* End of 'Eyes' function */

/* End of T02EYES.C file*/