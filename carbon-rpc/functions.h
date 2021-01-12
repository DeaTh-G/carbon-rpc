#pragma once
#include "include/discord/discord_rpc.h"
#include "include/discord/discord_register.h"
#include "Carbon/DAL/DALPursuit.h"
#include "Carbon/DAL/DALOptions.h"
#include "Carbon/DAL/DALCareer.h"
#include "Carbon/DAL/DALEvent.h"
#include "Carbon/DAL/DALRacer.h"
#pragma warning(disable:4996)

char StateBuf[128]{};
char DetailsBuf[128]{};
char LImgKeyBuf[128]{};
char LImgTxtBuf[128]{};
char SImgKeyBuf[128]{};
char SImgTxtBuf[128]{};

char PresenceStateBuf[128]{};
char PresenceDetailsBuf[128]{};
char PresenceLImgKeyBuf[128]{};
char PresenceLImgTxtBuf[128]{};
char PresenceSImgKeyBuf[128]{};
char PresenceSImgTxtBuf[128]{};

void UpdatePresenceData(DiscordRichPresence* presence,
    const char* state = NULL, const char* details = NULL,
    const char* largeImageKey = NULL, const char* largeImageText = NULL,
    const char* smallImageKey = NULL, const char* smallImageText = NULL,
    int64_t startTimestamp = NULL)
{
    if (presence->state)
        strcpy(StateBuf, presence->state);
    
    if (presence->details)
        strcpy(DetailsBuf, presence->details);

    if (presence->largeImageKey)
        strcpy(LImgKeyBuf, presence->largeImageKey);

    if (presence->largeImageText)
        strcpy(LImgTxtBuf, presence->largeImageText);

    if (presence->smallImageKey)
        strcpy(SImgKeyBuf, presence->smallImageKey);

    if (presence->smallImageText)
        strcpy(SImgTxtBuf, presence->smallImageText);

    if (state && strcmp(StateBuf, state) ||
        details && strcmp(DetailsBuf, details) ||
        largeImageKey && strcmp(LImgKeyBuf, largeImageKey) ||
        largeImageText && strcmp(LImgTxtBuf, largeImageText) ||
        smallImageKey && strcmp(SImgKeyBuf, smallImageKey) ||
        smallImageText && strcmp(SImgTxtBuf, smallImageText))
    {
        if (state)
            strcpy(PresenceStateBuf, state);

        if (details)
            strcpy(PresenceDetailsBuf, details);

        if (largeImageKey)
            strcpy(PresenceLImgKeyBuf, largeImageKey);

        if (largeImageText)
            strcpy(PresenceLImgTxtBuf, largeImageText);

        if (smallImageKey)
            strcpy(PresenceSImgKeyBuf, smallImageKey);

        if (smallImageText)
            strcpy(PresenceSImgTxtBuf, smallImageText);

        Discord_UpdatePresence(presence);
    }

    if (startTimestamp)
    {
        presence->startTimestamp = startTimestamp;
        Discord_UpdatePresence(presence);
    }
}

void GetCurrentPositionFormatted(char* posBuf)
{
    if (*(int*)(0x00A98284) > 0)
    {
        int currPos = *(int*)(*(int*)(0x00A98284) + 0x4C);

        if (currPos % 10 == 1 && currPos != 11)
            sprintf(posBuf, "%dst Place", currPos);
        else if (currPos % 10 == 2 && currPos != 12)
            sprintf(posBuf, "%dnd Place", currPos);
        else if (currPos % 10 == 3 && currPos != 13)
            sprintf(posBuf, "%dnd Place", currPos);
        else
            sprintf(posBuf, "%dth Place", currPos);
    }
}

void GetCashFormatted(char* cashBuf)
{
    int currCash = 0;
    DALCareer::GetCash(&currCash);

    if (currCash < 1000)
        sprintf(cashBuf, "Cash: %d", currCash);
    else if (currCash >= 1000 && currCash < 1000000)
        sprintf(cashBuf, "Cash: %d,%03d", currCash / 1000, currCash % 1000);
    else if (currCash >= 1000000 && currCash < 1000000000)
        sprintf(cashBuf, "Cash: %d,%03d,%03d", currCash / 1000000,
            currCash / 1000 % 1000, currCash % 1000);
    else
        sprintf(cashBuf, "Cash: %d,%03d,%03d,%03d", currCash / 1000000000,
            currCash / 1000000 % 1000, currCash / 1000 % 1000, currCash % 1000);
}

void GetCurrentLapFormatted(char* lapBuf, int eventHash)
{
    int numLaps = 0;
    DALEvent::GetEventNumLaps(&numLaps, eventHash);
    
    int currLap = 0;
    if (*(int*)(0x00A98284))
        currLap = *(int*)(*(int*)(0x00A98284) + 0x64);

    if (++currLap == numLaps)
        sprintf(lapBuf, "Final Lap");
    else if (currLap % 10 == 1 && currLap != 11)
        sprintf(lapBuf, "%dst Lap", currLap);
    else if (currLap % 10 == 2 && currLap != 12)
        sprintf(lapBuf, "%dnd Lap", currLap);
    else if (currLap % 10 == 3 && currLap != 13)
        sprintf(lapBuf, "%drd Lap", currLap);
    else
        sprintf(lapBuf, "%dth Lap", currLap);
}

int GetCurrentCanyonPhaseFormatted(char* phaseBuf, int eventHash)
{
    int canyonPhase = 0;
    DALEvent::GetEventCanyonPhase(&canyonPhase, eventHash);

    if (!canyonPhase)
        sprintf(phaseBuf, "Following Phase");
    else
        sprintf(phaseBuf, "Leading Phase");

    return canyonPhase;
}

int GetCurrentCanyonScoreFormatted(char* scoreBuf, int countDir)
{
    float currentScore = 0;
    DALRacer::GetCanyonHudScore(&currentScore, 0, countDir);
    
    int roundedScore = round(currentScore);
    if (roundedScore < 0)
        sprintf(scoreBuf, "0 pts", roundedScore);
    else if (roundedScore < 1000)
        sprintf(scoreBuf, "%d pts", roundedScore);
    else if (roundedScore >= 1000 && roundedScore < 1000000)
        sprintf(scoreBuf, "%d,%03d pts", roundedScore / 1000, roundedScore % 1000);
    else if (roundedScore >= 1000000 && roundedScore < 1000000000)
        sprintf(scoreBuf, "%d,%03d,%03d pts", roundedScore / 1000000,
            roundedScore / 1000 % 1000, roundedScore % 1000);
    else
        sprintf(scoreBuf, "%d,%03d,%03d,%03d pts", roundedScore / 1000000000,
            roundedScore / 1000000 % 1000, roundedScore / 1000 % 1000, roundedScore % 1000);

    return roundedScore;
}

int GetCurrentCanyonDistanceBehindFormatted(char* distBuf)
{
    float currentDistance = 0;
    DALRacer::GetCanyonDistanceBehind(&currentDistance, 3);

    DALOptions::UnitType currentUnit;
    DALOptions::GetSpeedoUnits(&currentUnit);
    if (currentUnit == DALOptions::SPEEDO_METRIC)
        sprintf(distBuf, "%.0f meters", round(currentDistance));
    else
        sprintf(distBuf, "%.0f feet", round(currentDistance));

    return round(currentDistance);
}

void GetCurrentSpeedtrapSpeedFormatted(char* speedBuf)
{
    float totalSpeed = 0;
    DALRacer::GetTotalSpeedtrapSpeed(&totalSpeed, 0);

    DALOptions::UnitType currentUnit;
    DALOptions::GetSpeedoUnits(&currentUnit);
    if (currentUnit == DALOptions::SPEEDO_METRIC)
        sprintf(speedBuf, "%.0f KM/H", round(totalSpeed));
    else
        sprintf(speedBuf, "%.0f MPH", round(totalSpeed));
}

void GetCurrentDriftTotalFormatted(char* scoreBuf)
{
    int totalScore = 0;
    DALRacer::GetDriftTotalPoints(&totalScore, 0);
    
    if (totalScore < 1000)
        sprintf(scoreBuf, "%d pts", totalScore);
    else if (totalScore >= 1000 && totalScore < 1000000)
        sprintf(scoreBuf, "%d,%03d pts", totalScore / 1000, totalScore % 1000);
    else if (totalScore >= 1000000 && totalScore < 1000000000)
        sprintf(scoreBuf, "%d,%03d,%03d pts", totalScore / 1000000,
            totalScore / 1000 % 1000, totalScore % 1000);
    else
        sprintf(scoreBuf, "%d,%03d,%03d,%03d pts", totalScore / 1000000000,
            totalScore / 1000000 % 1000, totalScore / 1000 % 1000, totalScore % 1000);
}

void GetCompletedPercentFormatted(char* percentBuf)
{
    float completionPercent = 0;
    DALRacer::GetPercentCompleted(&completionPercent, 0);

    sprintf(percentBuf, "Completion: %.0f%%", round(completionPercent));
}

void GetCheckpointsFormatted(char* pointBuf, int eventHash)
{
    int numLaps = 0;
    DALEvent::GetEventNumLaps(&numLaps, eventHash);

    int compLaps = 0;
    DALRacer::GetLapsCompleted(&compLaps, 0);

    sprintf(pointBuf, "%d : %d", compLaps, ++numLaps);
}

void GetRemainingTimeFormatted(char* timeBuf)
{
    float time = 0;
    DALRacer::GetRemainTime(&time, 0);

    int hours = time / 60 / 60;
    int minutes = time / 60;
    int seconds = (int)floor(time) % 60;
    int miliseconds = (int)((time - floor(time)) * 100);

    if (hours)
        sprintf(timeBuf, "%d:%02d:%02d.%02d", hours, minutes, seconds, miliseconds);
    else if (!hours && minutes)
        sprintf(timeBuf, "%d:%02d.%02d", minutes, seconds, miliseconds);
    else if (!hours && !minutes)
        sprintf(timeBuf, "%d.%02d", seconds, miliseconds);
}

void GetBountyFormatted(char* bountyBuf)
{
    float bounty = 0;
    DALPursuit::GetBounty(&bounty);
    int rdBounty = floor(bounty);

    if (rdBounty < 1000)
        sprintf(bountyBuf, "%d", rdBounty);
    else if (rdBounty >= 1000 && rdBounty < 1000000)
        sprintf(bountyBuf, "%d,%03d", rdBounty / 1000, rdBounty % 1000);
    else if (rdBounty >= 1000000 && rdBounty < 1000000000)
        sprintf(bountyBuf, "%d,%03d,%03d", rdBounty / 1000000,
            rdBounty / 1000 % 1000, rdBounty % 1000);
    else
        sprintf(bountyBuf, "%d,%03d,%03d,%03d", rdBounty / 1000000000,
            rdBounty / 1000000 % 1000, rdBounty / 1000 % 1000, rdBounty % 1000);
}

void GetNumCopsDestroyedFormatted(char* copBuf)
{
    int copNum = 0;
    DALPursuit::GetNumCopsDestroyed(&copNum);

    if (copNum < 1000)
        sprintf(copBuf, "%d", copNum);
    else if (copNum >= 1000 && copNum < 1000000)
        sprintf(copBuf, "%d,%03d", copNum / 1000, copNum % 1000);
    else if (copNum >= 1000000 && copNum < 1000000000)
        sprintf(copBuf, "%d,%03d,%03d", copNum / 1000000,
            copNum / 1000 % 1000, copNum % 1000);
    else
        sprintf(copBuf, "%d,%03d,%03d,%03d", copNum / 1000000000,
            copNum / 1000000 % 1000, copNum / 1000 % 1000, copNum % 1000);
}

void GetCostToStateFormatted(char* costBuf)
{
    float cost = 0;
    DALPursuit::GetCostToState(&cost);
    int rdCost = floor(cost);

    if (rdCost < 1000)
        sprintf(costBuf, "%d", rdCost);
    else if (rdCost >= 1000 && rdCost < 1000000)
        sprintf(costBuf, "%d,%03d", rdCost / 1000, rdCost % 1000);
    else if (rdCost >= 1000000 && rdCost < 1000000000)
        sprintf(costBuf, "%d,%03d,%03d", rdCost / 1000000,
            rdCost / 1000 % 1000, rdCost % 1000);
    else
        sprintf(costBuf, "%d,%03d,%03d,%03d", rdCost / 1000000000,
            rdCost / 1000000 % 1000, rdCost / 1000 % 1000, rdCost % 1000);
}

void GetCooldownTimeRemainingFormatted(char* timeBuf, float time)
{
    int hours = time / 60 / 60;
    int minutes = time / 60;
    int seconds = (int)floor(time) % 60;
    int miliseconds = (int)((time - floor(time)) * 100);

    if (hours)
        sprintf(timeBuf, "%d:%02d:%02d.%02d", hours, minutes, seconds, miliseconds);
    else if (!hours && minutes)
        sprintf(timeBuf, "%d:%02d.%02d", minutes, seconds, miliseconds);
    else if (!hours && !minutes)
        sprintf(timeBuf, "%d.%02d", seconds, miliseconds);
}