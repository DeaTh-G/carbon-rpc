#pragma once
#include "../../framework.h"

class DALEvent
{
public:
	inline static FUNCTION_PTR(bool, __stdcall, GetEventNumRacers, 0x004B3090, int* a1, int a2);
	inline static FUNCTION_PTR(bool, __stdcall, GetIsPursuit, 0x004B3180, int* a1, int a2);
	inline static FUNCTION_PTR(bool, __stdcall, GetEventCanyonPhase, 0x004A2970, int* a1, int a2);
	inline static FUNCTION_PTR(bool, __stdcall, GetEventNumLaps, 0x004A1E60, int* a1, int a2);
	inline static FUNCTION_PTR(bool, __stdcall, GetIsInFreeRoam, 0x004A2B60, bool* a1);
	inline static FUNCTION_PTR(bool, __stdcall, GetEventType, 0x004A2050, RaceType* a1, int a2);
	inline static FUNCTION_PTR(bool, __stdcall, GetEventHash, 0x004A25C0, int* eventHash, int a2);
	inline static FUNCTION_PTR(bool, __stdcall, GetEventName, 0x004A2F10, const char* eventName, int a2, int eventHash);
	inline static FUNCTION_PTR(bool, __stdcall, GetEventIsCareer, 0x004A21D0, int* flag, int a2);
	inline static FUNCTION_PTR(bool, __stdcall, GetEventIsChallenge, 0x004A2360, int* flag, int a2);
};