#pragma once

#include <algorithm>

struct Timer
{
    Timer();
    float totalTime();
    float deltaTime();

    void reset();
    void tick();
private:
    float mSecondPerCount{0.0f};
    float mDeltaTime{0.0f};
    int64_t mBaseTime{};
    int64_t mCurrentTime{};
    int64_t mPreviousTime{};
};
