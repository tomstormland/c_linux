#include <windows.h>

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
  wc.lpszClassName = "winapi_013_window_click";
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassEx(&wc)) {
    MessageBox(NULL, "Window registration failed!", "ERROR", MB_ICONEXCLAMATION|MB_OK);
    return -1;
  }

  hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "winapi_013_window_click", "winapi_013_window_click", WS_OVERLAPPED, 0, 0, 500, 500, NULL, NULL, hInstance, NULL);

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

