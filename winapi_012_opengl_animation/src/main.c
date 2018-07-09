#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <sys/timeb.h>

unsigned int windowWidth = 600;
unsigned int windowHeight = 600;

int msec = 0;
float sec = 0.0f;

struct timeb start, now;

float spin = 0.0f;

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
      } break;

    case WM_KEYDOWN:
      {
        /* close window when escape pressed */
        if (wParam == VK_ESCAPE) {
          PostMessage(hwnd, WM_CLOSE, 0, 0);
        }
      } break;

    case WM_SIZE:
      {
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        PostMessage(hwnd, WM_PAINT, 0, 0);
      } break;

    case WM_PAINT:
      {
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

  HWND hwnd;
  MSG msg;
  HDC hdc;
  HGLRC hrc;
  WNDCLASSW wc = {0};
  int pf;
  PIXELFORMATDESCRIPTOR pfd;

  wc.style = CS_OWNDC;
  wc.lpszClassName = L"winapi_012_opengl_animation";
  wc.hInstance = hInstance;
  wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wc.lpfnWndProc = WndProc;
  wc.hCursor = LoadCursor(0, IDC_ARROW);
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.lpszMenuName = NULL;

  RegisterClassW(&wc);
  hwnd = CreateWindow(wc.lpszClassName, L"winapi_012_opengl_animation", WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0, 0, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

  hdc = GetDC(hwnd);
  memset(&pfd, 0, sizeof(pfd));

  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;

  pf = ChoosePixelFormat(hdc, &pfd);

  SetPixelFormat(hdc, pf, &pfd);

  DescribePixelFormat(hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

  ReleaseDC(hwnd, hdc);

  hrc = wglCreateContext(hdc);
  wglMakeCurrent(hdc, hrc);

  ftime(&start);

  while (1) {
    ftime(&now);

    msec = 1000 * (now.time - start.time) + (now.millitm - start.millitm);
    sec = (float)msec / 1000.0f;

    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    if (msg.message == WM_QUIT) {
      break;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glShadeModel(GL_FLAT);

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.3f, 0.3f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glRotatef(spin, 0.0f, 0.0f, 1.0f);

    glBegin(GL_POLYGON);
    glVertex3f(-25.0f, -25.0f, 0.0f);
    glVertex3f(+25.0f, -25.0f, 0.0f);
    glVertex3f(+25.0f, +25.0f, 0.0f);
    glVertex3f(-25.0f, +25.0f, 0.0f);
    glEnd();

    glPopMatrix();

    spin = -(sec * 100.0f);

    glFlush();
  }

  return (int) msg.wParam;
}
