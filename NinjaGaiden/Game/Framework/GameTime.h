#pragma once
#include <Windows.h>
class GameTime
{
public:
	void StartCounter();
	float GetCouter();
	static GameTime* getInstance() {
		if (mInstance == NULL) mInstance = new GameTime();
		return mInstance;
	};
	~GameTime();

private:
	GameTime();
	LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockRate;
	static GameTime *mInstance;
};
