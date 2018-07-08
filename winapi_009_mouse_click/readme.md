winapi_007_center_window
========================

```c
... WM_CREATE:

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
```
