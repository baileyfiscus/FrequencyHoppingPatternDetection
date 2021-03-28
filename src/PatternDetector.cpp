#include <iostream>
#include <vector>

#include "PatternDetector.h"

PatternDetector::PatternDetector(Medium& medium)
    : mMedium(&medium)
{

}

void PatternDetector::DetectLoop()
{
    auto startingFreq = GetInitialFrequency();
    std::cout << "Found starting frequency of " << startingFreq << std::endl;
    std::vector<int> freqOrder;
    while (freqOrder.size() < mMedium->GetChannels()) {
        // Find the frequency pattern
        int freq = 0;
        freqOrder.push_back(freq);
    }

    std::vector<std::pair<int, int>> pattern;
    for (auto freq : freqOrder) {
        // Find the duration for each frequency
        int duration = 0;
        pattern.push_back(std::make_pair(freq, duration));
    }
}

int PatternDetector::GetInitialFrequency()
{
    int freq = 0;
    while (true) {
        if (mMedium->IsChannelActive(freq)) {
            return freq;
        }
        freq = (freq + 1) % 100; // todo determine or provide max number of channels
    }
}