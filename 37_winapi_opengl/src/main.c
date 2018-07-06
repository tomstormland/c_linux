#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

int win_x = 0;
int win_y = 0;
int win_width = 400;
int win_height = 400;

LONG WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

  static PAINTSTRUCT ps;

  switch (uMsg) {
    case WM_PAINT:
      {
        /* rotate a triangle around */
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(+0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(+0.0f, +0.5f, 0.0f);
        glEnd();
        glFlush();
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
      }
      break;
    case WM_SIZE:
      glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
      PostMessage(hWnd, WM_PAINT, 0, 0);
      break;
    case WM_CHAR:
      switch (wParam) {
        case 27:
          PostQuitMessage(0);
          break;
      }
      break;
    case WM_CLOSE:  
      PostQuitMessage(0);
      break;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hCurrentInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {

  int pf;
  HDC hDC;
  HGLRC hRC;
  HWND hWnd;
  PIXELFORMATDESCRIPTOR pfd;
  MSG msg;
  WNDCLASS wc;
  static HINSTANCE hInstance = 0;

  hInstance = GetModuleHandle(NULL);

  wc.style = CS_OWNDC;
  wc.lpfnWndProc = (WNDPROC)WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  /*wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);*/
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "OpenGL";

  if (!RegisterClass(&wc)) {
    printf("ERROR: 'Was unable to register window class.'.\n");
    return -1;
  }

  hWnd = CreateWindow("OpenGL", "OpenGL", WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, win_x, win_y, win_width, win_height, NULL, NULL, hInstance, NULL);

  if (hWnd == NULL) {
    printf("ERROR: 'Was unable to create window.'.\n");
    return -1;
  }

  hDC = GetDC(hWnd);

  memset(&pfd, 0, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;

  pf = ChoosePixelFormat(hDC, &pfd);

  if (pf == 0) {
    printf("ERROR: 'Was unable to find pixel format.'.\n");
    return -1;
  }

  if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
    printf("ERROR: 'Was unable to set pixel format.'.\n");
    return -1;
  }

  DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

  ReleaseDC(hWnd, hDC);

  hRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hRC);

  ShowWindow(hWnd, nCmdShow);

  while (GetMessage(&msg, hWnd, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
