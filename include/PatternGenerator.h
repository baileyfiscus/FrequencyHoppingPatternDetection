#pragma once

#include "Pattern.h"

class PatternGenerator
{
public:
    PatternGenerator(size_t channels, size_t minDuration, size_t maxDuration);
    ~PatternGenerator();
    Pattern* GetPattern();
private:
    size_t mChannels, mMinDuration, mMaxDuration;
    Pattern* mPattern;

    void ConstructPattern();
};
