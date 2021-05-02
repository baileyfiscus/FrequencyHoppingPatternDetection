#include <iostream>

#include "Pattern.h"

Pattern::Pattern(std::vector<std::pair<int, long>> patternVec)
    : mPatternVec(patternVec)
{
    mTotalDuration = 0;
    for (auto pair : mPatternVec) {
        mTotalDuration += pair.second;
    }
}

std::pair<int, long> Pattern::GetPairAt(int index)
{
    return mPatternVec[index];
}

int Pattern::GetFrequencyAt(int index)
{
    return mPatternVec[index].first;
}

long Pattern::GetDurationAt(int index)
{
    return mPatternVec[index].second;
}

std::vector<std::pair<int, long>> Pattern::GetVector()
{
    return mPatternVec;
}

size_t Pattern::GetLength()
{
    return mPatternVec.size();
}

long Pattern::GetTotalDuration()
{
    return mTotalDuration;
}

void Pattern::Print()
{
    for (auto itr = std::begin(mPatternVec); itr != std::end(mPatternVec); itr++) {
        std::cout << "Channel: " << itr->first << ", Duration: " << itr->second << std::endl;
    }
}
