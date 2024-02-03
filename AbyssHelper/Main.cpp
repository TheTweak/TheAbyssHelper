#include <windows.h>
#include <stdio.h>
#include <synchapi.h>
#include "SendKeys.h"


int main()
{
	while (1)
	{
		const TCHAR* region = GetCursorRegion(1279, 719);
		Sleep(10);
	}

	return 0;
}
