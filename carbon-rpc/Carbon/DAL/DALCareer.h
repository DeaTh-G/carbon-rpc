#pragma once
#include "../../framework.h"

class DALCareer
{
public:
	inline static FUNCTION_PTR(bool, __stdcall, GetCash, 0x004A0940, int* amount);
	inline static FUNCTION_PTR(bool, __stdcall, GetTutorialComplete, 0x004A0A90, int* isComplete);
	inline static FUNCTION_PTR(bool, __stdcall, GetProfileName, 0x004A0C10, const char* name, int a2);
	inline static FUNCTION_PTR(bool, __stdcall, GetCareerPercentComplete, 0x004CD1D0, float* a1);
	inline static FUNCTION_PTR(bool, __stdcall, GetGamePercentComplete, 0x004CD2B0, float* a1);
};