#pragma once

#include <vector>

#include "Device.h"

class PuzzlePiecePatternDetector : public Device
{
public:
    PuzzlePiecePatternDetector (std::size_t channelCount);
    virtual Operation GetOperation(int& frequency) override;
    virtual void SetListenResponse(bool bHeard) override;
    int GetFrequency();
private:
    std::size_t mChannelCount;
    std::vector<int> mPuzzle;
    std::vector<std::vector<int>> mPossiblePieces;

    static constexpr int const& INVALID_CHANNEL = -1;

    Device::Operation mNextOperation = Device::Operation::NOOP;
    int mLastFrequency;

    bool mCountFrequencyGuessDwell = false;
    bool mHeardLastResponse = false;
    bool mWaitForBurstEnd = true;
    bool mWaitForEndOfSequence = false;
    bool mGetNewGuess = false;
    bool mCheckIfHeard = false;
    std::size_t mPatternIndex = 0;
};