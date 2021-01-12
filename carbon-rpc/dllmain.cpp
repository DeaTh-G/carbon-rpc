// dllmain.cpp : defines the entry point for the dll application.
#include "pch.h"
#include "include/discord/discord_rpc.h"
#include "include/discord/discord_register.h"
#include "cars.h"
#include "racetypes.h"
#include "races.h"
#include "Carbon/DAL/DALCareer.h"
#include "Carbon/DAL/DALChallenge.h"
#include "Carbon/DAL/DALVehicle.h"
#include "Carbon/DAL/DALEvent.h"
#include "Carbon/Fe/FeGarageMain.h"
#include "Carbon/Game/GCareerZone.h"
#include "Carbon/Game.h"
#include "functions.h"
#include "hooks.h"
#include <ctime>

#pragma warning(disable:4996)

static DiscordRichPresence DiscordPresence;
char CurrentAreaName[128]{};

void InitDiscord()
{
    Discord_Initialize("777559148027576351", NULL, 1, NULL);
    memset(&DiscordPresence, 0, sizeof(DiscordPresence));
    DiscordPresence.state = PresenceStateBuf;
    DiscordPresence.details = PresenceDetailsBuf;
    DiscordPresence.largeImageKey = PresenceLImgKeyBuf;
    DiscordPresence.largeImageText = PresenceLImgTxtBuf;
    DiscordPresence.smallImageKey = PresenceSImgKeyBuf;
    DiscordPresence.smallImageText = PresenceSImgTxtBuf;

    UpdatePresenceData(&DiscordPresence, NULL, "Booting up...", "game_logo", "Need for Speed: Carbon", NULL, NULL, std::time(nullptr));
}
HOOK(int, __cdecl, MainLoop, 0x006B7930, float a1)
{
    int result = originalMainLoop(a1);
    
    char nameBuf[128]{};

    int eventHash = 0;
    RaceType type = (RaceType)-1;
    const char* raceMap = "";

    DALEvent::GetEventHash(&eventHash, 0xFFFFFFFF);
    DALEvent::GetEventName(nameBuf, 0x80, eventHash);
    DALEvent::GetEventType(&type, eventHash);

    if (type <= 0)
    {
        char profNameBuf[128]{};
        char carPercentBuf[128]{};
        char chalPercentBuf[128]{};
        char gamePercentBuf[128]{};
        DALCareer::GetProfileName(profNameBuf, 0x20);

        /* This is more like Game_IsFreeRoam */
        if (Game_IsCareerMode())
        {
            char carBuf[128]{};
            const char* carName = (const char*)(*(int*)(0x00A8AD54) - 0x68);
            if (CAR_MAP.contains(carName))
                sprintf(carBuf, "car_%s", CAR_MAP.at(carName));
            
            /* This version of the SDK doesn't support 'é' so we are fixing it this way! */
            if (!strcmp(carName, "Lamborghini Murciélago"))
                carName = "Lamborghini Murcielago";
            else if (!strcmp(carName, "Lamborghini Murciélago LP640"))
                carName = "Lamborghini Murcielago LP640";

            char terrBuf[128]{};

            int isPursuit = false;
            DALEvent::GetIsPursuit(&isPursuit, 0xFFFFFFFF);
            if (isPursuit)
            {
                if (type != RACE_PURSUIT_END)
                {
                    int isBusted = false;
                    DALPursuit::GetIsPlayerBusted(&isBusted);
                    if (!isBusted)
                    {
                        char stateBuf[128]{};
                        char detailsBuf[128]{};

                        float timeRemain = 0;
                        float timeRequire = 0;
                        DALPursuit::GetCooldownTimeRemaining(&timeRemain);
                        DALPursuit::GetCooldownTimeRequired(&timeRequire);
                        if (std::abs(timeRequire - timeRemain) > 0.001f)
                        {
                            char timeBuf[128]{};
                            GetCooldownTimeRemainingFormatted(timeBuf, timeRemain);
                            sprintf(stateBuf, "Time to escape: %s", timeBuf);

                            UpdatePresenceData(&DiscordPresence, stateBuf, "Cooldown");
                        }
                        else
                        {
                            char bountyBuf[128]{};
                            GetBountyFormatted(bountyBuf);
                            float heatLevel = 0;
                            DALVehicle::GetHeat(&heatLevel, 0);
                            sprintf(detailsBuf, "Bounty: %s (Heat %.0f)", bountyBuf, floor(heatLevel));

                            char costBuf[128]{};
                            GetCostToStateFormatted(costBuf);
                            char copBuf[128]{};
                            GetNumCopsDestroyedFormatted(copBuf);
                            sprintf(stateBuf, "Cost to State: %s (Cops Disabled: %s)", costBuf, copBuf);

                            UpdatePresenceData(&DiscordPresence, stateBuf, detailsBuf);
                        }

                        UpdatePresenceData(&DiscordPresence, NULL, NULL, "world_pursuit", "Pursuit");
                    }
                    else
                    {
                        UpdatePresenceData(&DiscordPresence, "", "Busted!", "world_pursuit", "Pursuit");
                    }
                }
                else
                {
                    UpdatePresenceData(&DiscordPresence, "", "Pursuit Escaped!", "world_pursuit", "Pursuit");
                }
            }
            else
            {
                if (!IsWorldMapOpen)
                    UpdatePresenceData(&DiscordPresence, CurrentAreaName, "Currently Exploring", "world_freeroam", "Free Roam");
            }

            UpdatePresenceData(&DiscordPresence, NULL, NULL, NULL, NULL, carBuf, carName);
        }
        else if (strcmp(profNameBuf, "Player"))
        {
            char cashBuf[128]{};
            GetCashFormatted(cashBuf);

            float completionPercent = 0;
            if (*(int**)dword_BBAA8C)
            {
                switch (FeGarageMain::GetSafehouseType(*(int**)dword_BBAA8C))
                {
                case SAFEHOUSE_MUSCLE:
                case SAFEHOUSE_TUNER:
                case SAFEHOUSE_EXOTIC:
                case SAFEHOUSE_GENERIC:
                    DALCareer::GetCareerPercentComplete(&completionPercent);
                    sprintf(carPercentBuf, "Career Completion: %.0f%%", floor(completionPercent * 100));
                    UpdatePresenceData(&DiscordPresence, cashBuf, carPercentBuf, "world_safehouse", "Safehouse", "", "");
                    break;
                case SAFEHOUSE_MAIN:
                    DALChallenge::GetChallengeSeriesCompletePercent(&completionPercent);
                    sprintf(chalPercentBuf, "Challenge Series Completion: %.0f%%", floor(completionPercent));
                    DALCareer::GetGamePercentComplete(&completionPercent);
                    sprintf(gamePercentBuf, "Game Completion: %.0f%%", floor(completionPercent * 100));
                    UpdatePresenceData(&DiscordPresence, chalPercentBuf, gamePercentBuf, "game_logo", "Main Menu", "", "");
                    break;
                case SAFEHOUSE_STARTER:
                    UpdatePresenceData(&DiscordPresence, "", "Choosing a starter car...", "game_logo", "Need for Speed: Carbon", "", "");
                    break;
                case CAR_LOT_MUSCLE:
                case CAR_LOT_TUNER:
                case CAR_LOT_EXOTIC:
                case CAR_LOT_MAZDA:
                    UpdatePresenceData(&DiscordPresence, cashBuf, "", "world_carlot", "Car Lot", "", "");
                    break;
                default:
                    UpdatePresenceData(&DiscordPresence, "", "", "game_logo", "Need for Speed: Carbon", "", "");
                    break;
                }
            }
        }
    }
    else
    {
    int numRacers = -1;
    DALEvent::GetEventNumRacers(&numRacers, eventHash);

    if (numRacers >= 0)
    {
        char carBuf[128]{};
        char typeBuf[128]{};
        char posBuf[128]{};

        GetCurrentPositionFormatted(posBuf);

        if (type == RACE_CIRCUIT || type == RACE_RACE_WARS)
        {
            char lapBuf[128]{};
            GetCurrentLapFormatted(lapBuf, eventHash);


            if (CIRCUIT_MAP.contains(nameBuf))
                raceMap = CIRCUIT_MAP.at(nameBuf);
            else if (type == RACE_CIRCUIT)
                raceMap = "race_circuit";
            else if (type == RACE_RACE_WARS)
                raceMap = "race_racewars";

            if (RACE_MAP.contains(type))
                sprintf(typeBuf, "%s (%s)", RACE_MAP.at(type), lapBuf);
        }
        else if (type == RACE_SPRINT || type == RACE_CANYON_SPRINT)
        {
            char percentBuf[128]{};
            GetCompletedPercentFormatted(percentBuf);

            if (SPRINT_MAP.contains(nameBuf))
                raceMap = SPRINT_MAP.at(nameBuf);
            else
                raceMap = "race_sprint";

            if (RACE_MAP.contains(type))
                sprintf(typeBuf, "%s (%s)", RACE_MAP.at(type), percentBuf);
        }
        else if (type == RACE_DRIFT || type == RACE_CANYON_DRIFT)
        {
            char scoreBuf[128]{};
            GetCurrentDriftTotalFormatted(scoreBuf);

            if (DRIFT_MAP.contains(nameBuf))
                raceMap = DRIFT_MAP.at(nameBuf);
            else
                raceMap = "race_drift";

            if (RACE_MAP.contains(type))
                sprintf(typeBuf, "%s (%s)", RACE_MAP.at(type), scoreBuf);
        }
        else if (type == RACE_CHECKPOINT)
        {
            char pointBuf[128]{};
            GetCheckpointsFormatted(pointBuf, eventHash);

            char timeBuf[128]{};
            GetRemainingTimeFormatted(timeBuf);

            if (CHECKPOINT_MAP.contains(nameBuf))
                raceMap = CHECKPOINT_MAP.at(nameBuf);
            else
                raceMap = "race_checkpoint";

            if (RACE_MAP.contains(type))
                sprintf(typeBuf, "%s (%s)", RACE_MAP.at(type), pointBuf);

            sprintf(posBuf, "Time Left: %s", timeBuf);
        }
        else if (type == RACE_SPEEDTRAP)
        {
            char speedBuf[128]{};
            GetCurrentSpeedtrapSpeedFormatted(speedBuf);

            if (SPEEDTRAP_MAP.contains(nameBuf))
                raceMap = SPEEDTRAP_MAP.at(nameBuf);
            else
                raceMap = "race_speedtrap";

            if (RACE_MAP.contains(type))
                sprintf(typeBuf, "%s (%s)", RACE_MAP.at(type), speedBuf);
        }
        else if (type == RACE_CANYON_DUEL)
        {
            int phaseTotal = 0;

            int currPhase = GetCurrentCanyonPhaseFormatted(posBuf, eventHash);

            char scoreBuf[128]{};
            GetCurrentCanyonScoreFormatted(scoreBuf, currPhase);

            char distBuf[128]{};
            int currDist = GetCurrentCanyonDistanceBehindFormatted(distBuf);

            if (CANYON_MAP.contains(nameBuf))
                raceMap = CANYON_MAP.at(nameBuf);
            else
                raceMap = "race_canyon";

            if (currDist < 0)
                if (currPhase == DALRacer::PHASE_FOLLOWING)
                    sprintf(posBuf, "Opponent Passed!");
                else
                    sprintf(posBuf, "Passed!");
            else
                sprintf(posBuf, "%s (Distance: %s)", posBuf, distBuf);

            if (RACE_MAP.contains(type))
                sprintf(typeBuf, "%s (%s)", RACE_MAP.at(type), scoreBuf);
        }
        else if (type == RACE_PURSUIT_TAG)
        {
            raceMap = "race_pursuit_tag";
            sprintf(nameBuf, "");
        }
        else if (type == RACE_PURSUIT_KNOCKOUT)
        {
            raceMap = "race_pursuit_knockout";
            sprintf(nameBuf, "");
        }
        else if (type == RACE_RANDOM_ENCOUNTER)
        {
            char percentBuf[128]{};
            GetCompletedPercentFormatted(percentBuf);

            raceMap = "race_random_encounter";
            sprintf(nameBuf, "");
        }
        else if (type == RACE_PURSUIT_CHALLENGE)
        {
            int isBusted = false;
            DALPursuit::GetIsPlayerBusted(&isBusted);
            if (!isBusted)
            {
                char stateBuf[128]{};
                char detailsBuf[128]{};

                float timeRemain = 0;
                float timeRequire = 0;
                DALPursuit::GetCooldownTimeRemaining(&timeRemain);
                DALPursuit::GetCooldownTimeRequired(&timeRequire);
                if (std::abs(timeRequire - timeRemain) > 0.001f)
                {
                    char timeBuf[128]{};
                    GetCooldownTimeRemainingFormatted(timeBuf, timeRemain);
                    sprintf(stateBuf, "Time to escape: %s", timeBuf);

                    UpdatePresenceData(&DiscordPresence, stateBuf, "Cooldown");
                }
                else
                {
                    char bountyBuf[128]{};
                    GetBountyFormatted(bountyBuf);
                    float heatLevel = 0;
                    DALVehicle::GetHeat(&heatLevel, 0);
                    sprintf(detailsBuf, "Bounty: %s (Heat %.0f)", bountyBuf, floor(heatLevel));

                    char costBuf[128]{};
                    GetCostToStateFormatted(costBuf);
                    char copBuf[128]{};
                    GetNumCopsDestroyedFormatted(copBuf);
                    sprintf(stateBuf, "Cost to State: %s (Cops Disabled: %s)", costBuf, copBuf);

                    UpdatePresenceData(&DiscordPresence, stateBuf, detailsBuf);
                }
            }
            else
            {
                UpdatePresenceData(&DiscordPresence, "", "Busted!");
            }

        }

        int isCareerEvent = 0;
        const char* carName = "";
        DALEvent::GetEventIsCareer(&isCareerEvent, eventHash);
        if (isCareerEvent)
        {
            carName = (const char*)(*(int*)(0x00A8AD54) - 0x68);

            if (eventHash == 0x99C27E3B)
                carName = "BMW M3 GTR";
        }
        else
        {
            int isChallenge = 0;
            DALEvent::GetEventIsChallenge(&isChallenge, eventHash);
            if (isChallenge)
            {
                int carHash;
                DALChallenge::GetChallengeCarNameHash(&carHash, eventHash);

                /* Couldn't figure out a better way to get the car names,
                so I'm using this custom value as the key to access the car names.
                This will not with work with mods that tweak the Challenge Series!!! */
                int csCarKey = abs(carHash - eventHash);
                if (CS_CAR_MAP.contains(csCarKey))
                    carName = CS_CAR_MAP.at(csCarKey);
            }
            else
            {
                carName = (const char*)(*(int*)(0x00A8AD50) + 0x78);
            }
        }

        if (CAR_MAP.contains(carName))
        {
            sprintf(carBuf, "car_%s", CAR_MAP.at(carName));
            UpdatePresenceData(&DiscordPresence, NULL, NULL, NULL, NULL, carBuf, carName);
        }

        // Convert race name to Title Case
        for (size_t i = 0; i < strlen(nameBuf); i++)
        {
            if (i == 0 || nameBuf[i] == ' ' || nameBuf[i] == '\'' || (i - 1 > 0 && nameBuf[i - 1] == ' '))
                continue;

            nameBuf[i] += 0x20;
        }

        if (!strcmp(nameBuf, "Default String"))
            strcpy(nameBuf, "");

        int isRaceFinished = 0;
        DALRacer::GetIsFinished(&isRaceFinished, 0);
        if (type != RACE_PURSUIT_CHALLENGE)
        {
            if (!isRaceFinished)
                UpdatePresenceData(&DiscordPresence, posBuf, typeBuf, raceMap, nameBuf);
            else
                UpdatePresenceData(&DiscordPresence, posBuf, "Race Finished!", raceMap, nameBuf);
        }
        else
        {
            strcat(nameBuf, " (Pursuit Challenge)");
            UpdatePresenceData(&DiscordPresence, NULL, NULL, "world_pursuit", nameBuf);
        }
    }
    }

    return result;
}

HOOK(const char*, __fastcall, GCareerZoneGetName, 0x00617C00, int* This, void* edx)
{
    const char* currAreaName = originalGCareerZoneGetName(This, edx);

    strcpy(CurrentAreaName, currAreaName);
    for (size_t i = 0; i < strlen(CurrentAreaName); i++)
    {
        if (i == 0 || CurrentAreaName[i] == ' ' || (i - 1 > 0 && CurrentAreaName[i - 1] == ' '))
            continue;

        CurrentAreaName[i] += 0x20;
    }

    return currAreaName;
}

void Init()
{
    INSTALL_HOOK(MainLoop);
    INSTALL_HOOK(GCareerZoneGetName);
    INSTALL_HOOK(WorldMap__ct);
    INSTALL_HOOK(WorldMap__dt);
}

DWORD WINAPI Looper(LPVOID lpParam)
{
    InitDiscord();
    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
        IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
        IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

        if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x87E926) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
        {
            Init();
            CreateThread(0, 0, Looper, hModule, 0, NULL);
        }

        else
        {
            MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.4 English nfsc.exe (6,88 MB (7.217.152 bytes)).", "Carbon-RPC", MB_ICONERROR);
            return FALSE;
        }
    }

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}