#include <windows.h>
#include <wchar.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow) {

  wchar_t lpText[100] = L"LOREM CONTENT";
  wchar_t lpCaption[100] = L"SCREEN SIZE";

  int w = GetSystemMetrics(SM_CXSCREEN);
  int h = GetSystemMetrics(SM_CYSCREEN);

  swprintf(lpText, 100, L"%d x %d", w, h);

  MessageBoxW(NULL, (LPCWSTR)lpText, (LPCWSTR)lpCaption, MB_OK);

  return 0;
}
