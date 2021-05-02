#pragma once

#include <vector>

class Pattern
{
public:
    Pattern(std::vector<std::pair<int, long>> patternVec);
    std::pair<int, long> GetPairAt(int index);
    int GetFrequencyAt(int index);
    long GetDurationAt(int index);
    std::vector<std::pair<int, long>> GetVector();
    size_t GetLength();
    long GetTotalDuration();
    void Print();
private:
    std::vector<std::pair<int, long>> mPatternVec;
    long mTotalDuration;
};