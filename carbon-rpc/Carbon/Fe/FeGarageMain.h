#pragma once
#include "../../framework.h"

static int* dword_BBAA8C = (int*)0x00BBAA8C;

enum SafehouseType {
	SAFEHOUSE_NONE = 0,
	SAFEHOUSE_MUSCLE = 1,
	SAFEHOUSE_TUNER = 2,
	SAFEHOUSE_EXOTIC = 3,
	CAR_LOT_MUSCLE = 4,
	CAR_LOT_TUNER = 5,
	CAR_LOT_EXOTIC = 6,
	CAR_LOT_MAZDA = 7,
	SAFEHOUSE_MAIN = 8,
	SAFEHOUSE_GENERIC = 9,
	SAFEHOUSE_STARTER = 10
};

class FeGarageMain
{
public:
	inline static FUNCTION_PTR(SafehouseType, __thiscall, GetSafehouseType, 0x0083F110, int* This);
};