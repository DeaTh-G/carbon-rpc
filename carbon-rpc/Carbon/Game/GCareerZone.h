#pragma once
#include "../../framework.h"

static int GManager = 0x009D8ADC;

class GCareerZone
{
public:
	inline static FUNCTION_PTR(const char*, __thiscall, GetName, 0x00617C00, int* This);
	inline static FUNCTION_PTR(int, __thiscall, GetHeatLevel, 0x0062EC30, int* This);
};