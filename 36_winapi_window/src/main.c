#define _UNICODE

#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int window_width = 400;
int window_height = 400;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR lpCmdLine, int nCmdShow) {

  MSG  msg;
  WNDCLASSW wc = {0};

  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpszClassName = L"Rectangle";
  wc.hInstance     = hInstance;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  /*wc.hbrBackground = (HBRUSH)GetSysColorBrush(0);*/
  wc.lpfnWndProc   = WndProc;
  wc.hCursor       = LoadCursor(0, IDC_ARROW);

  RegisterClassW(&wc);
  CreateWindowW(wc.lpszClassName, L"Rectangle",
      WS_OVERLAPPED|WS_VISIBLE,
      100, 100, window_width, window_height, NULL, NULL, hInstance, NULL);

  while (GetMessage(&msg, NULL, 0, 0)) {

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

  HDC hdc;
  PAINTSTRUCT ps;

  switch(msg) {

    case WM_CREATE:
      {
        /* set window background color to white */
        HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);
      }
      break;

    case WM_KEYDOWN:

      /* close window on escape key */
      if (wParam == VK_ESCAPE) {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
      }

      break;

    case WM_PAINT:
      {

        RECT rect;
        hdc = BeginPaint(hwnd, &ps);

        int center_x = window_width / 2;
        int center_y = window_height / 2;

        rect.left = center_x - 50;
        rect.top = center_y - 50;
        rect.right = center_x + 50;
        rect.bottom = center_y + 50;

        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

        /* draw line [TOP LEFT] to [BOTTOM RIGHT] */
        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, window_width, window_height);
        /* draw line [BOTTOM LEFT] to [TOP RIGHT] */
        MoveToEx(hdc, 0, window_height, NULL);
        LineTo(hdc, window_width, 0);
        EndPaint(hwnd, &ps);
      }
      break;

    case WM_DESTROY:

      PostQuitMessage(0);
      return 0;
  }

  return DefWindowProcW(hwnd, msg, wParam, lParam);
}
