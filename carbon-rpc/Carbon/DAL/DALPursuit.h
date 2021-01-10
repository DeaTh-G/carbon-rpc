#pragma once
#include "../../framework.h"

class DALPursuit
{
public:
	inline static FUNCTION_PTR(bool, __stdcall, GetCooldownTimeRequired, 0x004C99E0, float* a1);
	inline static FUNCTION_PTR(bool, __stdcall, GetCooldownTimeRemaining, 0x004C9A50, float* a1);
	inline static FUNCTION_PTR(bool, __stdcall, GetCostToState, 0x004C9CA0, float* a1);
	inline static FUNCTION_PTR(bool, __stdcall, GetBounty, 0x004C9D20, float* a1);
	inline static FUNCTION_PTR(bool, __stdcall, GetIsPlayerBusted, 0x004C9E20, int* a1);
	inline static FUNCTION_PTR(bool, __stdcall, GetNumCopsDestroyed, 0x004CA040, int* a1);
};