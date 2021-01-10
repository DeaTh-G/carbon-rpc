#pragma once
#include "../../framework.h"

class DALOptions
{
public:
	enum UnitType {
		SPEEDO_IMPERIAL,
		SPEEDO_METRIC
	};

	inline static FUNCTION_PTR(bool, __stdcall, GetSpeedoUnits, 0x004A4550, UnitType* type);
};