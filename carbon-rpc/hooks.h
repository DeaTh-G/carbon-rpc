#pragma once
#include "framework.h"
int IsWorldMapOpen;
int IsNISPlaying;

HOOK(int, __fastcall, WorldMap__ct, 0x005CF130, int* This, void* edx, int* a2)
{
	int result = originalWorldMap__ct(This, edx, a2);
	IsWorldMapOpen = true;
	return result;
}

HOOK(int, __fastcall, WorldMap__dt, 0x005C3160, int* This, void* edx, int a2)
{
	int result = originalWorldMap__dt(This, edx, a2);
	IsWorldMapOpen = false;
	return result;
}