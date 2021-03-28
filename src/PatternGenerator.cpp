#include <random>
#include <algorithm>
#include "PatternGenerator.h"

PatternGenerator::PatternGenerator(int channels, int minDuration, int maxDuration)
    : mChannels(channels)
    , mMinDuration(minDuration)
    , mMaxDuration(maxDuration)
{
    ConstructPattern();
}

void PatternGenerator::ConstructPattern()
{
    // Create the random frequency order
    std::vector<int> freqOrder;
    for (int i = 0; i < mChannels; i++) { freqOrder.push_back(i); }
    std::random_device rd;
    std::mt19937 rand(rd());
    std::shuffle(freqOrder.begin(), freqOrder.end(), rand);

    // Create the random duration for each frequency
    for (auto freq : freqOrder) {
        int dur = std::rand() % (mMaxDuration - mMinDuration + 1);
        mPattern.push_back(std::make_pair(freq, dur));
    }
}

std::vector<std::pair<int, int>> PatternGenerator::GetPattern()
{
    return mPattern;
}
