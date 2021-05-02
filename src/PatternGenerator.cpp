#include <algorithm>
#include <iostream>
#include <random>

#include "PatternGenerator.h"

PatternGenerator::PatternGenerator(size_t channels, size_t minDuration, size_t maxDuration)
    : mChannels(channels)
    , mMinDuration(minDuration)
    , mMaxDuration(maxDuration)
{
    ConstructPattern();
}

PatternGenerator::~PatternGenerator()
{
    delete mPattern;
}

void PatternGenerator::ConstructPattern()
{
    // Create the random frequency order
    std::vector<int> freqOrder;
    for (int i = 0; i < mChannels; i++) { freqOrder.push_back(i); }
    std::random_device rd;
    std::mt19937 rand(rd());
    std::shuffle(freqOrder.begin(), freqOrder.end(), rand);

    std::vector<std::pair<int, long>> patternVec;

    // Create the random duration for each frequency
    for (auto freq : freqOrder) {
        long dur = static_cast<long>(std::rand() % (mMaxDuration - mMinDuration + 1));
        patternVec.push_back(std::make_pair(freq, dur));
    }

    mPattern = new Pattern(patternVec);
}

Pattern* PatternGenerator::GetPattern()
{
    return mPattern;
}
