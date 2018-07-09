#include <windows.h>
#include <resource.h>

const int ID_TIMER = 1;
const int BALL_MOVE_DELTA = 3;

typedef struct _BALLINFO {
  int width;
  int height;

  int x;
  int y;

  int dx;
  int dy;
} BALLINFO;

BALLINFO ballInfo;
HBITMAP hBitmapBall = NULL;
HBITMAP hBitmapMask = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg) {
    case WM_CREATE: 
      {
        /* set window background color to white */
        HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);

        /* center the window */
        RECT rc = { 0 };

        GetWindowRect(hwnd, &rc);

        int windowW = rc.right - rc.left;
        int windowH = rc.bottom - rc.top;

        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);

        int x = (screenW - windowW) / 2;
        int y = (screenH - windowH) / 2;

        SetWindowPos(hwnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);

        /* TODO: Name the section. */
        UINT ret;
        BITMAP bitmap;

        hBitmapBall = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BALL));
        if (hBitmapBall == NULL) {
          MessageBox(hwnd, "Unable to load IDI_BALL", "ERROR", MB_OK);
        }

        /* create bitmap mask */
        {
          COLORREF transparent;
          HDC hdcA, hdcB;
          BITMAP bitmap;

          transparent = RGB(0, 0, 0);

          GetObject(hBitmapBall, sizeof(BITMAP), &bitmap);
          hBitmapMask = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, 1, NULL);

          hdcA = CreateCompatibleDC(0);
          hdcB = CreateCompatibleDC(0);

          SelectObject(hdcA, hBitmapBall);
          SelectObject(hdcB, hBitmapMask);

          SetBkColor(hdcA, transparent);

          BitBlt(hdcA, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcA, 0, 0, SRCCOPY);
          BitBlt(hdcB, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcB, 0, 0, SRCINVERT);

          DeleteDC(hdcA);
          DeleteDC(hdcB);
        }

        if (hBitmapMask == NULL) {
          MessageBox(hwnd, "Unable to create mask", "ERROR", MB_OK);
        }

        GetObject(hBitmapBall, sizeof(bitmap), &bitmap);

        ZeroMemory(&ballInfo, sizeof(ballInfo));
        ballInfo.width = bitmap.bmWidth;
        ballInfo.height = bitmap.bmHeight;

        ballInfo.dx = BALL_MOVE_DELTA;
        ballInfo.dy = BALL_MOVE_DELTA;

        ret = SetTimer(hwnd, ID_TIMER, 10, NULL);
        if (ret == 0) {
          MessageBox(hwnd, "COULD NOT SET TIMER", "ERROR", MB_OK);
        }
      } break;
    case WM_PAINT:
      {
        RECT client;
        PAINTSTRUCT ps;
        HDC hdc;

        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &client);

        /* draw the ball */
        HDC hdcBuffer = CreateCompatibleDC(hdc);
        HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, client.right, client.bottom);
        HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmapMask);

        FillRect(hdcBuffer, &client, (HBRUSH)GetStockObject(WHITE_BRUSH));

        BitBlt(hdcBuffer, ballInfo.x, ballInfo.y, ballInfo.width, ballInfo.height, hdcMem, 0, 0, SRCAND);

        SelectObject(hdcMem, hBitmapBall);
        BitBlt(hdcBuffer, ballInfo.x, ballInfo.y, ballInfo.width, ballInfo.height, hdcMem, 0, 0, SRCPAINT);

        BitBlt(hdc, 0, 0, client.right, client.bottom, hdcBuffer, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hbmOld);
        DeleteDC(hdcMem);

        SelectObject(hdcBuffer, hbmOldBuffer);
        DeleteDC(hdcBuffer);
        DeleteObject(hbmBuffer);

        EndPaint(hwnd, &ps);

      } break;
    case WM_TIMER:
      {
        RECT client;
        HDC hdc;

        hdc = GetDC(hwnd);

        GetClientRect(hwnd, &client);

        /* update ball (&client) */
        ballInfo.x += ballInfo.dx;
        ballInfo.y += ballInfo.dy;

        if (ballInfo.x < 0) {
          ballInfo.x = 0;
          ballInfo.dx = BALL_MOVE_DELTA;
        } else if (ballInfo.x + ballInfo.width > client.right) {
          ballInfo.x = client.right - ballInfo.width;
          ballInfo.dx = -BALL_MOVE_DELTA;
        }

        if (ballInfo.y < 0) {
          ballInfo.y = 0;
          ballInfo.dy = BALL_MOVE_DELTA;
        } else if (ballInfo.y + ballInfo.height > client.bottom) {
          ballInfo.y = client.bottom - ballInfo.height;
          ballInfo.dy = -BALL_MOVE_DELTA;
        }

        /* draw ball again */
        HDC hdcBuffer = CreateCompatibleDC(hdc);
        HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, client.right, client.bottom);
        HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hBitmapMask);

        FillRect(hdcBuffer, &client, (HBRUSH)GetStockObject(WHITE_BRUSH));

        BitBlt(hdcBuffer, ballInfo.x, ballInfo.y, ballInfo.width, ballInfo.height, hdcMem, 0, 0, SRCAND);

        SelectObject(hdcMem, hBitmapBall);
        BitBlt(hdcBuffer, ballInfo.x, ballInfo.y, ballInfo.width, ballInfo.height, hdcMem, 0, 0, SRCPAINT);

        BitBlt(hdc, 0, 0, client.right, client.bottom, hdcBuffer, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hbmOld);
        DeleteDC(hdcMem);

        SelectObject(hdcBuffer, hbmOldBuffer);
        DeleteDC(hdcBuffer);
        DeleteObject(hbmBuffer);

        ReleaseDC(hwnd, hdc);
      } break;
    case WM_KEYDOWN:
      {
        /* close window when escape pressed */
        if (wParam == VK_ESCAPE) {
          PostMessage(hwnd, WM_CLOSE, 0, 0);
        }
      } break;
    case WM_LBUTTONDOWN:
      {
        char szFileName[MAX_PATH];
        HINSTANCE hInstance = GetModuleHandle(NULL);

        GetModuleFileName(hInstance, szFileName, MAX_PATH);
        MessageBox(hwnd, szFileName, "File: ", MB_OK|MB_ICONINFORMATION);
      } break;
    case WM_CLOSE:
      {
        DestroyWindow(hwnd);
      } break;
    case WM_DESTROY:
      {
        PostQuitMessage(0);
      } break;
    default:
      {
        return DefWindowProc(hwnd, msg, wParam, lParam);
      } break;
  }

  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

  WNDCLASSEX wc;
  HWND hwnd;
  MSG msg;

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = 0;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "winapi_014_animation_one";
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassEx(&wc)) {
    MessageBox(NULL, "Window registration failed!", "ERROR", MB_ICONEXCLAMATION|MB_OK);
    return -1;
  }

  hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "winapi_014_animation_one", "winapi_014_animation_one", WS_OVERLAPPED, 0, 0, 500, 500, NULL, NULL, hInstance, NULL);

  if (hwnd == NULL) {
    MessageBox(NULL, "Window creation failed.", "ERROR", MB_OK);
    return -1;
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}

