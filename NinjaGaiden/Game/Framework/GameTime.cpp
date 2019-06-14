#include "GameTime.h"

GameTime *GameTime::mInstance = NULL;

GameTime::GameTime()
{

}

GameTime::~GameTime()
{
}


void GameTime::StartCounter()
{
	if (!QueryPerformanceFrequency(&mClockRate))
	{
		return;
	}

	QueryPerformanceCounter(&mStartTime);

}

float GameTime::GetCouter()
{
	QueryPerformanceCounter(&mEndTime);
	mDelta.QuadPart = mEndTime.QuadPart - mStartTime.QuadPart;

	return ((float)mDelta.QuadPart / mClockRate.QuadPart);
}
