#pragma once
#include "../../framework.h"

class DALChallenge
{
public:
	inline static FUNCTION_PTR(bool, __stdcall, GetChallengeSeriesCompletePercent, 0x004AA730, float* a1);
	inline static FUNCTION_PTR(bool, __stdcall, GetChallengeDebugCarName, 0x004AA840, const char* a1, int a2, int a3);
	inline static FUNCTION_PTR(bool, __stdcall, GetChallengeCarNameHash, 0x004B72D0, int* a1, int a2);
};