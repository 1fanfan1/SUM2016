/*FILE NAME: T03POLE.C
 *PROGRAMMER: SA
 *DATE: 03.06.2016
 *PURPOSE: WinApi
*/
#pragma warning(disable: 4244)
#pragma warning(disable: 4013)
#include <windows.h>
#include <stdlib.h>
#include <math.h>

LRESULT CALLBACK MyWinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID Arrow( HWND hWnd, HDC hDC, INT X, INT Y );
VOID FlipFullScreen( HWND hWnd );

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
  //HFONT hFnt;
  //CHAR Text[100] = "© Shvetz Corporation, 2016"
  PAINTSTRUCT ps;
  INT i = 0, j = 0, k = 0, l = 0;

  static INT w, h, dx = 1, dy = 1, plusdx = 4, plusdy = 4/*, dy1 = 600, dx1 = 600, plusdx1 = 4, plusdy1 = 4*/;
  static HDC hMemDC;
  static HBITMAP hBm;
  static BITMAP bm;
  MINMAXINFO *MinMax;
  
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    MinMax = (MINMAXINFO *)lParam;
    MinMax->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    FlipFullScreen(hWnd);
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
    
    if (dx >= w - 500 || dx <= 0)
      plusdx = -plusdx;
    if (dy >= h - 500 || dy <= 0)
      plusdy = -plusdy;

    dx += plusdx;
    dy += plusdy;

    for (i = 0; i <= 500; i += 25)
      for (j = 0; j <= 500; j += 25)
        Arrow(hWnd, hMemDC, i + dx, j + dy);
    /*       //One more square
    if (dx1 >= w - 300 || dx1 <= 0)
      plusdx1 = -plusdx1;
    if (dy1 >= h - 300 || dy1 <= 0)
      plusdy1 = -plusdy1;

    dx1 += plusdx1;
    dy1 += plusdy1;
   
    for (k = 0; k <= 300; k += 25)
      for (l = 0; l <= 300; l += 25)
        Arrow(hWnd, hMemDC, k + dx1, l + dy1);
    */
    //hFnt = CreateFont(211, 0, 50, 0, FW_BOLD, TRUE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_DECORATIVE, "");
    //SelectObject(hMemDC, hFnt);
    //SetTextColor(hMemDC, RGB(0, 0, 0));
    //SetBkColor(hMemDC, RGB(255, 255, 255));
    //SetBkMode()

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
  case WM_KEYDOWN:
    if (LOWORD(wParam) == 'F')
      FlipFullScreen(hWnd);
    else if (LOWORD(wParam) == VK_ESCAPE)
      DestroyWindow(hWnd);
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

/*Begin of 'Arrow' function */
VOID Arrow( HWND hWnd, HDC hDC, INT X, INT Y )
{
  HBRUSH hBrush, hOldBrush;
  static POINT pt, pts[] = 
  {
    {0, -15}, {0, 15}, {55, 0}
  }, 
  pts1[] = 
  {
    {0, -15}, {0, 15}, {-55, 0}  
  }; 
  POINT pt1[sizeof(pts) / sizeof(pts[0])], pt2[sizeof(pts1) / sizeof(pts1[0])];
  INT i;
   
  DOUBLE si, co;
 
  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);

  co = (pt.x - X) / sqrt((pt.x - X) * (pt.x - X) + (pt.y - Y) * (pt.y - Y));
  si = (Y - pt.y) / sqrt((pt.x - X) * (pt.x - X) + (pt.y - Y) * (pt.y - Y));

  for (i = 0; i < sizeof(pts) / sizeof(pts[0]); i++)
  {
    pt1[i].x = X + pts[i].x * co - pts[i].y * si;
    pt1[i].y = Y - pts[i].x * si - pts[i].y * co;
  }

  for (i = 0; i < sizeof(pts1) / sizeof(pts1[0]); i++)
  {
    pt2[i].x = X + pts1[i].x * co - pts1[i].y * si;
    pt2[i].y = Y - pts1[i].x * si - pts1[i].y * co;
  }

  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(0, 0, 0));
  srand(clock() / 1000);
  hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
  hOldBrush = SelectObject(hDC, hBrush);
  SetDCPenColor(hDC, RGB(0, 0, 0));
  
  Polygon(hDC, pt1, sizeof(pts) / sizeof(pts[0]));
  
  SelectObject(hDC, hOldBrush);
  DeleteObject(hBrush);

  hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
  hOldBrush = SelectObject(hDC, hBrush);

  Polygon(hDC, pt2, sizeof(pts1) / sizeof(pts1[0]));

  SelectObject(hDC, hOldBrush);
  DeleteObject(hBrush);
}   /* End of 'Arrow' function */

/* Set/reset full screen mode function */
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (IsFullScreen)
  {
    /* restore window size */
    SetWindowPos(hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Set full screen size to window */
    HMONITOR hmon;
    MONITORINFOEX moninfo;                       
    RECT rc;

    /* Store window old size */
    GetWindowRect(hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Obtain monitor info */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* Set window new size */
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOPMOST,
      rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
} /* End of 'FlipFullScreen' function */


/* End of T02EYES.C file*/