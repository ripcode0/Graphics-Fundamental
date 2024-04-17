#include "Timer.h"
#include <windows.h>

Timer::Timer()
{
    int64_t countPerSec{};
    QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSec);
    mSecondPerCount = 1.0f / (float)countPerSec;
    reset();
}

float Timer::totalTime()
{
    return (float)(mCurrentTime - mBaseTime) * mSecondPerCount;
}

float Timer::deltaTime()
{
    return mDeltaTime;
}

void Timer::reset()
{
    int64_t curTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
    mBaseTime = curTime;
    mPreviousTime = curTime;
}

void Timer::tick()
{
    int64_t curTime{};
    QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

    mCurrentTime = curTime;

    mDeltaTime = (mCurrentTime - mPreviousTime) * mSecondPerCount;

    mPreviousTime = mCurrentTime;

    if(mDeltaTime < 0.0f) mDeltaTime = 0.0f;
}
