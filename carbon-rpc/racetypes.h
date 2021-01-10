#pragma once
#include <map>

enum RaceType {
	RACE_PURSUIT_END,
	RACE_CIRCUIT,
	RACE_SPRINT,
	RACE_CANYON_SPRINT,
	RACE_UNKNOWN_TYPE_1,
	RACE_DRIFT,
	RACE_CANYON_DRIFT,
	RACE_CHECKPOINT,
	RACE_SPEEDTRAP,
	RACE_CANYON_DUEL,
	RACE_PURSUIT_TAG,
	RACE_PURSUIT_KNOCKOUT,
	RACE_RANDOM_ENCOUNTER,
	RACE_PURSUIT_CHALLENGE,
	RACE_RACE_WARS
};

std::map<int, const char*> RACE_MAP = {
	{ 0,  "Pursuit End" },
	{ 1,  "Circuit" },
	{ 2,  "Sprint" },
	{ 3,  "Canyon Sprint" },
	{ 4,  "Unknown Type" },
	{ 5,  "Drift" },
	{ 6,  "Canyon Drift" },
	{ 7,  "Checkpoint" },
	{ 8,  "Speedtrap" },
	{ 9,  "Canyon Duel" },
	{ 10, "Pursuit Tag" },
	{ 11, "Pursuit Knockout" },
	{ 12, "Random Encounter" },
	{ 13, "Pursuit Challenge" },
	{ 14, "Race Wars" }
};