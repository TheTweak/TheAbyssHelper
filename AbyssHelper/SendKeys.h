#pragma once
#include <winuser.h>

void SendKeys();
CURSORINFO GetCursorInfo();
const TCHAR* GetCursorRegion(UINT screenWidth, UINT screenHeight);
