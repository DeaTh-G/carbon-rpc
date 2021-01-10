#pragma once
#include "../../framework.h"

class DALRacer
{
public:
	enum PhaseType {
		PHASE_FOLLOWING,
		PHASE_LEADING
	};

	inline static FUNCTION_PTR(bool, __stdcall, GetCanyonHudScore, 0x004A6BE0, float* score, int playerID, int phase);
	inline static FUNCTION_PTR(bool, __stdcall, GetCanyonDistanceBehind, 0x004A6E00, float* distance, int playerID);
	inline static FUNCTION_PTR(bool, __stdcall, GetDriftTotalPoints, 0x004A6F20, int* score, int playerID);
	inline static FUNCTION_PTR(bool, __stdcall, GetPercentCompleted, 0x004CA680, float* percent, int playerID);
	inline static FUNCTION_PTR(bool, __stdcall, GetRemainTime, 0x004CA9B0, float* time, int playerID);
	inline static FUNCTION_PTR(bool, __stdcall, GetTotalSpeedtrapSpeed, 0x004CAC80, float* speed, int playerID);
	inline static FUNCTION_PTR(bool, __stdcall, GetLapsCompleted, 0x004CB070, int* laps, int playerID);
	inline static FUNCTION_PTR(bool, __stdcall, GetIsFinished, 0x004CF0F0, int* isFinished, int playerID);

	inline static FUNCTION_PTR(bool, __stdcall, GetCurrCarName, 0x004CF0F0, const char* carName, int carHash);
};