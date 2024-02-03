#include <windows.h>
#include <stdio.h>
#include "Utils.h"

void PrintLastError()
{
	DWORD lastError = ::GetLastError();
	LPVOID lpMsgBuf;
	::FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		lastError,
		0,
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	printf("Last error (code=%d): %ws\n", lastError, (LPTSTR)lpMsgBuf);
}
