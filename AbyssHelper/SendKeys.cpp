#include <Windows.h>
#include <stdio.h>
#define _USE_MATH_DEFINES // for C++
#include <math.h>
#include "Utils.h"
#include "SendKeys.h"

#define ORIGIN_X 0.5
#define ORIGIN_Y 0.5
#define RADIAN_DEGREES 180 / M_PI

void SendKeys()
{
	INPUT inputs[2] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = 'S';

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = 'S';
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inputs))
	{
		PrintLastError();
	}
}

CURSORINFO GetCursorInfo()
{
	CURSORINFO cursorInfo = { sizeof(CURSORINFO) };
	BOOL r = GetCursorInfo(&cursorInfo);
	if (!r)
	{
		PrintLastError();
	}
	return cursorInfo;
}

const TCHAR* GetCursorRegion(UINT screenWidth, UINT screenHeight)
{
	CURSORINFO cursorInfo = GetCursorInfo();
	LONG translatedX = cursorInfo.ptScreenPos.x + 1 - screenWidth / 2.0;
	LONG translatedY = screenHeight / 2.0 - cursorInfo.ptScreenPos.y + 1;
	FLOAT angle = atanf((FLOAT)abs(translatedY) / abs(translatedX)) * RADIAN_DEGREES;
	if		(translatedX < 0 && translatedY >= 0) { angle = 180.0 - angle; }
	else if (translatedX <= 0 && translatedY < 0) { angle = 180.0 + angle; }
	else if (translatedX > 0 && translatedY < 0)  { angle = 360.0 - angle; }

	/*
	NE: 0
	N : 1
	NW: 2
	W : 3
	SW: 4
	S : 5
	SE: 6
	E : 7
	*/
	static const TCHAR* regions[] = {TEXT("NE"), TEXT("N"), TEXT("NW"), TEXT("W"), TEXT("SW"), TEXT("S"), TEXT("SE"), TEXT("E")};
	UINT region = 0;
	if		(angle >= 22.5 && angle <= 22.5 + 45.0)	         region = 1;
	else if (angle >= 22.5 + 45.0 && angle <= 22.5 + 90.0)   region = 2;
	else if (angle >= 22.5 + 90.0 && angle <= 22.5 + 135.0)  region = 3;
	else if (angle >= 22.5 + 135.0 && angle <= 22.5 + 180.0) region = 4;
	else if (angle >= 22.5 + 180.0 && angle <= 22.5 + 225.0) region = 5;
	else if (angle >= 22.5 + 225.0 && angle <= 22.5 + 270.0) region = 6;
	else if (angle >= 22.5 + 270.0 && angle <= 22.5 + 315.0) region = 7;

	printf(
		"x=%d tx=%d y=%d ty=%d angle=%f region=%ws\n",
		cursorInfo.ptScreenPos.x,
		translatedX,
		cursorInfo.ptScreenPos.y,
		translatedY,
		angle,
		regions[region]
	);

	return regions[region];
}
 