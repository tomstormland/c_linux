#include <windows.h>
#include <stdio.h>

unsigned int windowWidth = 600;
unsigned int windowHeight = 600;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;

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

      } break;

    case WM_KEYDOWN:
      {
        /* close window when escape pressed */
        if (wParam == VK_ESCAPE) {
          PostMessage(hwnd, WM_CLOSE, 0, 0);
        }
      } break;

    case WM_PAINT:
      {
        RECT rect;

        hdc = BeginPaint(hwnd, &ps);

        int centerX = windowWidth / 2;
        int centerY = windowHeight / 2;

        /* draw lines to help see that rect is center */
        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, windowWidth, windowHeight);
        MoveToEx(hdc, 0, windowHeight, 0);
        LineTo(hdc, windowWidth, 0);

        /* create / set up and draw rect */

        rect.left = centerX - 50;
        rect.top = centerY - 50;
        rect.right = centerX + 50;
        rect.bottom = centerY + 50;

        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

        EndPaint(hwnd, &ps);
      } break;

    case WM_DESTROY:
      {
        PostQuitMessage(0);
        return 0;
      } break;

  }

  return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{

  MSG msg;

  WNDCLASSW wc = {0};

  wc.style = CS_HREDRAW|CS_VREDRAW;
  wc.lpszClassName = L"winapi_001_window";
  wc.hInstance = hInstance;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc = WndProc;
  wc.hCursor = LoadCursor(0, IDC_ARROW);

  RegisterClassW(&wc);
  CreateWindow(wc.lpszClassName, L"winapi_001_window", WS_OVERLAPPEDWINDOW|WS_VISIBLE, 0, 0, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int) msg.wParam;
}
