#include <windows.h>
#include <wchar.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow) {

  wchar_t computerName[MAX_COMPUTERNAME_LENGTH + 1]; 
  DWORD size = sizeof(computerName) / sizeof(computerName[0]);

  int r = GetComputerNameW(computerName, &size);

  wchar_t lpText[100] = L"LOREM CONTENT";
  wchar_t lpCaption[100] = L"COMPUTER NAME";

  swprintf(lpText, 100, L"%s", computerName);

  MessageBoxW(NULL, (LPCWSTR)lpText, (LPCWSTR)lpCaption, MB_OK);

  return 0;
}
