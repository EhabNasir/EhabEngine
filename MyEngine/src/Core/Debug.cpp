#include "Debug.h"

void Debug::PrintNumber(float _number)
{
	char buffer[64];
	sprintf_s(buffer, "y = %.5f\n", _number);
	OutputDebugStringA(buffer);
}
