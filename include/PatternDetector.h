#pragma once

#include <vector>
#include <chrono>

#include "Device.h"

class PatternDetector : public Device
{
public:
    PatternDetector(size_t channelCount);
    virtual Operation GetOperation(int& frequency) override;
    virtual void SetListenResponse(bool bHeard) override;
    int GetFrequency();
    void FindDuration();
    void FindPatternLength();
private:
    enum Status {
        FIND_FREQUENCY,
        FIND_DURATION,
        FIND_PATTERN_LENGTH,
        DONE
    };

    size_t mChannelCount;
    size_t mPatternLength = 0;
    size_t mCurrentDuration = 0;
    size_t mCurrentIndex = 0;

    int mFrequencyGuess = 0;
    int mLastFrequency = 0;

    bool mCountFrequencyGuessDwell = false;
    bool mHeardLastResponse = false;
    bool mWaitForBurstEnd = true;
    bool mWaitForEndOfSequence = false;
    bool mGetNewGuess = false;
    bool mCheckIfHeard = false;

    Status mStatus = Status::FIND_FREQUENCY;
    Operation mNextOperation = Operation::NOOP;

    std::vector<int> mFrequencyOrder;
    std::vector<long> mDurationOrder;

};
