#pragma once
#include <string>
#include <Windows.h>
#include <stdio.h>

class Debug
{
public:
	static void PrintNumber(float _number);

	static int VDebugPrintF(const char* _format, va_list _args)
	{
		const UINT32 maxChar = 1024;
		static char s_buffer[maxChar];

		int charsWritten = vsnprintf(s_buffer, maxChar, _format, _args);
		OutputDebugStringA(s_buffer);

		return charsWritten;
	}

	static int DebugPrintArguments(const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);

		int charsWritten = VDebugPrintF(_format, argList);
		va_end(argList);

		return charsWritten;
	}
};
