#include <windows.h>
#include <Lmcons.h>
#include <wchar.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow) {

  wchar_t username[UNLEN+1];
  DWORD len = sizeof(username) / sizeof(wchar_t);

  int r = GetUserNameW(username, &len);

  wchar_t lpText[100] = L"LOREM CONTENT";
  wchar_t lpCaption[100] = L"USERNAME";

  swprintf(lpText, 100, L"%s", username);

  MessageBoxW(NULL, (LPCWSTR)lpText, (LPCWSTR)lpCaption, MB_OK);

  return 0;
}
